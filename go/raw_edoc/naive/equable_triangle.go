package naive

func EquableTriangle(a, b, c int) bool {
	a, b, c = a*2, b*2, c*2
	p := (a + b + c) / 2
	s2 := p * (p - a) * (p - b) * (p - c)
	return p * p * 16 == s2
}
