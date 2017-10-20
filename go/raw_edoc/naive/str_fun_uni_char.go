package naive

import (
	"reflect"
	"fmt"
)

func StrFunUniChar(str string) bool {
	table := make(map[int32]bool)

	for _, c := range str {
		fmt.Println(reflect.TypeOf(c))
		if _, ok := table[c]; ok {  // TIP check key in map
			return false
		}
		table[c] = true
	}

	return true
}
