//
// see https://doc.rust-lang.org/book/first-edition/guessing-game.html

extern crate rand;

use std::io;
use std::cmp::Ordering;
use rand::Rng;

mod another;
use another::another_pub_fn;

fn main() {
	another_pub_fn();

    println!("Guess the number!");

    let secret_number = rand::thread_rng().gen_range(1, 101);

    loop {
	    println!("Please input a positive number as your guess.");

	    let mut guess = String::new();

	    io::stdin().read_line(&mut guess).expect("Failed to read line");

	    let guess: u32 = match guess.trim().parse() {
	    	Ok(num)	=> num,
	    	Err(_)	=> continue,
	    };

	    println!("You guessed: {}", guess);

	    match guess.cmp(&secret_number) {
	    	Ordering::Less		=> println!("Too small"),
	    	Ordering::Greater	=> println!("Too big!"),
	    	Ordering::Equal		=> {
	    		println!("You win!");
	    		break;
	    	}
	    }
	}
}

#[test]
fn it_works() {}

#[test]
fn it_works_2() {}

#[test]
#[ignore]
fn test_to_ignore() {} // run with "cargo test -- --ignored"

