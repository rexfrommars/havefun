package naive

import (
	"testing"
	"fmt"
)

func TestFizzBuzzCuckooClock(t *testing.T) {

	table := [][]string {
		{"10:03", "Fizz"},
		{"10:05", "Buzz"},
		{"10:15", "Fizz Buzz"},
		{"10:30", "Cuckoo"},
	}

	for index, duo := range table {
		fmt.Println(index, duo[0], duo[1])
		if actual := FizzBuzzCuckooClock(duo[0]); actual != duo[1] {
			t.Error("Unexpected result for setting <%s>: %s", duo, actual)
		}
	}
}
