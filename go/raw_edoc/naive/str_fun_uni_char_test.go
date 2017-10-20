package naive

import (
	"testing"
)

func TestStrFunUniChar(t *testing.T) {
	cases := []struct {
		uni bool
		str string
	} {
		{ true, "abc"},
		{ false, "hello"},
	}

	for _, case_ := range cases {
		if StrFunUniChar(case_.str) != case_.uni {
			t.Error("unecpect result for %s", case_.str)
		}
	}
}
