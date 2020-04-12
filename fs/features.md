
# Filesystem Assignment Features

 - Read / write more than one block.
 - Directories
 - Hard Links
 - Symbolic Links
 - Permissions and Timestamps
 - COW: Versions
 - COW: Rollback

## Read / write more than one block

Starter code:

 - Design assumption inode# = block# = dirent#.

Hints code inode structure:

 - int size;
 - int ptrs[2];   // direct pointers
    (if size == 0, no data blocks)
    (if size <= 4096, 1 data block, so ptrs[0] is used)
    (if size <= 8192, 2 data blocks, both ptrs[0] and ptrs[1] are used)
 - int iptr;
    - point to an entire block of extra pointers - index [>=2, <1026]
 
The # of blocks in a 1MB filesystem, given 4096 byte blocks (same as "pages") is
256, therefore one indirect pointer is more than enough.


 - Update inode to support multiple blocks
 - Handle reading / writing to any block
   - Example: Read 5000 from offset = 5000
     - Page 0 is 0..4096, so no bytes from there.
     - Page 1 is 4096..8192,
       - So copying from byte 4 to byte 4096 of page 1
       - That's 4092 bytes.
     - Page 2 is 8192..12288
       - We need to copy 908 bytes
       - That's byte 0 through byte 908 of page 2.
   - Loop through pages we need to read / write.
   - For the ones and the end, need to calc start and end.
   
 - How is this impacted by COW?
   - When we're writing to a block we first need to copy it. 
     - Copy old data block to new data block
     - Make the same write we would have made to that page before.
     - Need to update inode with the new block (same as "page") #.
   - Copy the inode, write new block numbers to copy. 
     - If this modified our indirect pointers block, then that needs
       to get copied and modified too.
     - This produces a new inode number.
   - Then we need to propagate the change up the tree.
     - New inode number means new directory entry, etc.

## Nested Directories 
 
Starter code:

 - Design assumption inode# = block# = dirent#.

New plan:

 - A directory is a Map data structure.
 - Map<String, Int>, specifically mapping file name to inode #.

Laziest solution:

 - A directory is an array of dirents.
 - Number of entries in directory = size / sizeof(dirent)

Dirent structure:

typedef struct dirent {
    char name[28];
    int  inum;
} dirent;

old dirent structure

typedef struct old_dirent {
    char name[...];
};

Resizeable array = vector = ArrayList

Directory data, 32 bytes per line:

size = 64 
-- start --
hi.txt	5
goat.txt   12
-- end -- 

Dealing with paths

Starter code:

    path: "/foo.txt"
    delete slash, lookup: "foo.txt"

New plan:

    path "/foo/bar/baz.txt"
    split: ["foo", "bar", "baz.txt"]
    - Look up "foo" in root
    - Look up "bar" in foo
    - Look up "baz.txt" in bar

How to handle with COW?

 - The thing that changes is writes (to directories)
   - That's delete, mknod, rename, ...
   - That's any file operation, since those change inode #
   - Really, any operation
 - Updating directory data block produces new block #
 - That produces new inode and new inode #
 - That triggers update to parent.
 - Final result is new root inode #.
 
# Hard Links

 - A hard link is just a dirent.

size = 96 
-- start --
hi.txt	5
goat.txt   12
hi2.txt	5
-- end -- 

```
$ ln hi.txt hi2.txt
```

 - Link count
 
The above ln command increased the link count from 1 to 2.

When a link is removed (unlink), decrease ref count.

If ref count goes to zero, remove the inode and data.


COW:

 - GC means we don't need link count.
 - But every update needs to update every reference
 
 -- start --
hi.txt	5
goat.txt   12
hi2.txt	5
-- end -- 

 -- start --
hi.txt	7
goat.txt   12
hi2.txt	7
-- end -- 

 - Three ideas:
   - Just scan the whole directory tree for refs.
   - Track all hard links in inode (can just be a list of directory inode #'s).
   - Add a layer of indirection.
     - mknod allocates a unique and unchanging virtual inode #
     - COW operations change a physical inode #
     - need translation table for virtual -> physical inode numbers
     - Maybe a 1 page table for each version
     - Disadvantage: Need the translation table
     - Advantage: Writes might not actually update directory path
       - Directories map names to virtual inode #'s
       - Only physical inode #'s actually change
       - So changes don't change parent directories
       - A version no longer creates a new root inode #
       - Instead it creates a new translation table page #

typedef struct inode {
    int mode; // permission & type
    int size; // bytes
    int ptrs[2]; // direct pointers
    int iptr; // single indirect pointer
    int backptrs[10];  // directories that reference this inode
    int ibackptrs;  // single indirect backpointers
} inode;


## Symbolic Links

 - You're going to need to add some new FUSE callbacks
   - Look in /usr/include/fuse/fuse.h
 - The symlink callback gives you a path and a target.
 - The readlink callback gives you a path, you give back the target.
 - Easiest plan: Store the target string in the assocated data block

Q: Implications of COW?
A: Nothing suprising.

## Permissions and Timestamps

 - Two callbacks:
   - chmod
     - just store permissions, don't break type
   - utimens
     - Gives two timestamps, you need to give back 3 on stat.

In both cases what we're doing is:

 - Use the path to find an inode.
 - Update some metadata in the inode.

Implications of COW: You updated an inode.


## Copy on Write: Versions and Rollback

 - Version table
   - Map<Version #, {Root Directory Inode #, Note string}>
   - Map<Version #, {Inode Map Block #, Note string}>
 - Current version

```
struct cow_version {
    int vnum;
    int root_inode_num;
    char note[24];
}
```

General plan:

 - You're already doing recursive traversals for update.
 - New versions of those functions that return a positive
   new inode # or block # on success.

Example:

 - Write to data block returns int (block #) to write-to-inode.
 - Write-to-inode returns int (# inode #) to write-to-directory.
 - Write-to-directory returns int (block #) to whatever called it.
 - Etc.
 - Eventually write-to-fs(path, buffer, size, offset) returns int (inode #)
   which is the new root.
 - Write that to your version table.
