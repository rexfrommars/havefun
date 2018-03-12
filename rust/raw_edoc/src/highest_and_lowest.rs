
//
// str.split_whitespace()
// Option.unwrap()
//

fn _high_and_low(numbers: &str) -> String {
  let mut ns = numbers.split_whitespace();
  let mut h = ns.next().unwrap().parse::<i32>().unwrap();
  let mut l = h;
  for n in ns {
  	println!("{}", n);
  	let i = n.parse::<i32>().unwrap();
  	if i > h { h = i; }
  	if i < l { l = i; }
  }
  return format!("{} {}", h, l);
}

#[test]
fn test() {
	let result = _high_and_low("8 3 -5 42 -1 0 0 -9 4 7 4 -4");
	println!("{}", result);
  assert_eq!(result, "42 -9")
}
