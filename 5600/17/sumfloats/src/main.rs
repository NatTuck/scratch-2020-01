
use std::io::{Cursor, Read, Seek, SeekFrom};
use std::fs::File;

extern crate bytes;
use bytes::Buf;

fn main() {
    // Open the file
    let mut file = File::open("/tmp/data.dat").unwrap();
    file.seek(SeekFrom::Start(8)).unwrap();

    // Read the floats and add them up
    let mut sum = 0f32;

    for _ii in 0..4 {
        let mut tmp = [0u8; 4];
        file.read_exact(&mut tmp).unwrap();
        let xx = Cursor::new(tmp).get_f32_le();
        sum += xx;
    }

    // Print result
    println!("sum = {}", sum);
}
