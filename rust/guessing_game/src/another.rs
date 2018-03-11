

fn another_fn() {}

pub fn another_pub_fn() {
	another_fn();
}

#[cfg(test)]
mod tests {
	use super::*; // otherwise another_fn would not be found

	#[test]
	fn another_test() {
		another_fn();
	}
}
