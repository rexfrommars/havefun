package naive

import (
	"reflect"
	"testing"
)

/*
	see also bytes.Equal()

	It is said that reflect.DeepEqual()is slow.
	see:
		http://www.tapirgames.com/blog/golang-slice-comparison
		http://programming.guide/go/compare-slices.html
 */

func TestSquareOrSquareRoot(t *testing.T) {

	cases := [][][]int{
		{{4, 3, 9, 7, 2, 1}, {2, 9, 3, 49, 4, 1}},
		{{100, 101, 5, 5, 1, 1}, {10, 10201, 25, 25, 1, 1}},
		{{1, 2, 3, 4, 5, 6}, {1, 4, 9, 2, 25, 36}},
	}

	for _, duo := range cases {
		result := SquareOrSquareRoot(duo[0])
		if !reflect.DeepEqual(result, duo[1]) { // TIP: reflect.DeepEqual
			t.Error("unexpected: ", result, duo[1])
		}
	}
}
