
# Notes on File System starter code

 - starter code
   - minimal file system
 - hints directory
   - some ideas of how to struture more complicated filesystem
 - create disk image
   - ./nufs new ...
 - make mount
   - assumes disk image is "data.nufs"

# Stuff we've learned

 - 1 MB disk image = 256 pages = 256 blocks
 - Block #0?
   - Array of inodes (256 = 2048 bytes)
 - Block #1 is the root directory
 - That leaves inodes and blocks #2 - #255 for file data blocks
 
