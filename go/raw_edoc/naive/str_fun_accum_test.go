package naive

import (
	"testing"
)

func TestStrFunAccum(t *testing.T) {
	cases := [][]string {
		{
			"abcd",
			"A-Bb-Ccc-Dddd",
		},
	}

	for _, duo := range cases {
		result := StrFunAccum(duo[0])
		if result != duo[1] {
			t.Error("unexpected result: ", duo[1], result)
		}
	}
}
