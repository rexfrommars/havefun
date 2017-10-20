package naive

import (
	"bytes"
	"strings"
)

/*
	TIP strings.ToUpper
	TIP strings.ToLower
	TIP strings.Join

	see also:
		Unicode
 */

func StrFunAccum(s string) string {
	var buff bytes.Buffer
	for i := 0; i < len(s); i++ {

		up, low := strings.ToUpper(s[i:i+1]), strings.ToLower(s[i:i+1])
		buff.WriteString(up)
		for j := 0; j < i; j++ {
			buff.WriteString(low)
		}
		buff.WriteString("-")

		//up, low := s[i], s[i]
		//if 'a' <= up && up <= 'z' {
		//	up -= 'a' - 'A'
		//}
		//if 'A' <= low && low <= 'Z' {
		//	low += 'a' - 'A'
		//}
		//buff.WriteByte(up)
		//for j := 0; j < i; j++ {
		//	buff.WriteByte(low)
		//}
		//buff.WriteString("-")
	}
	result := buff.String()
	return result[:len(result) - 1]
}
