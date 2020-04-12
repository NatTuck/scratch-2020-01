
use std::thread;
//use std::sync::{Arc, Mutex};

fn main() {
    let top:i64 = 1000 * 1000 * 1000;
    let each = top / 10;

    let mut kids = vec![];

    for tid in 0..10 {
        kids.push(thread::spawn(move || {
            let mut sum = 0i64;
            let i0 = tid * each;
            let i1 = i0 + each;

            for ii in i0..i1 {
                if ii % 101 == 0 {
                    sum += ii;
                }
            }

            sum
        }));
    }

    let mut sum = 0;

    for tt in kids {
        sum += tt.join().unwrap();
    }

    println!("sum = {}", sum);
}
