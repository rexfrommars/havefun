
fn hor_mirror(s: String) -> String {
	// your code
	let mut ll = s.split("\n");
	s
}

fn vert_mirror(s: String) -> String {
	// your code
	s
}

// // first parameter: dots have to be replaced by function of one variable
// fn oper(..., s: String) -> String {
//     // your code
// }

// fn testing1(s: &str, exp: &str) -> () {
//     assert_eq!(oper(hor_mirror, s.to_string()), exp)
// }
// fn testing2(s: &str, exp: &str) -> () {
//     assert_eq!(oper(vert_mirror, s.to_string()), exp)
// }

// #[test]
// fn basics_oper() {

//     testing1("lVHt\nJVhv\nCSbg\nyeCt", "yeCt\nCSbg\nJVhv\nlVHt");
//     testing1("njMK\ndbrZ\nLPKo\ncEYz", "cEYz\nLPKo\ndbrZ\nnjMK");
//     testing1("QMxo\ntmFe\nWLUG\nowoq", "owoq\nWLUG\ntmFe\nQMxo");
    
//     testing2("hSgdHQ\nHnDMao\nClNNxX\niRvxxH\nbqTVvA\nwvSyRu", "QHdgSh\noaMDnH\nXxNNlC\nHxxvRi\nAvVTqb\nuRySvw");
//     testing2("IzOTWE\nkkbeCM\nWuzZxM\nvDddJw\njiJyHF\nPVHfSx", "EWTOzI\nMCebkk\nMxZzuW\nwJddDv\nFHyJij\nxSfHVP");
//     testing2("cuQW\nxOuD\nfZwp\neqFx", "WQuc\nDuOx\npwZf\nxFqe");
// }

#[test]
fn test() {
	hor_mirror("abcd\n1234".to_string());
	vert_mirror("abcd\n1234".to_string());
}
