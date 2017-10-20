package naive

import (
	"testing"
)

func TestEquableTriangle(t *testing.T) {
	cases := []struct {
		equable bool
		a, b, c int
	} {
		{true, 5, 12, 13},
		{false, 2, 3, 4},
	}

	for _, _case := range cases {
		if result := EquableTriangle(_case.a, _case.b, _case.c); result != _case.equable {
			t.Error("exception:", _case)
		}
	}
}