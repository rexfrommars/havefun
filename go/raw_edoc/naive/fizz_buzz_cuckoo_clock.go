package naive

import (
	"strings"
	//"bytes"
	"strconv"
	"fmt"
)

func FizzBuzzCuckooClock(time string) string {
	fmt.Println(time)
	duo := strings.Split(time, ":")
	h, _ := strconv.Atoi(duo[0])
	h %= 12
	if h == 0 {
		h = 12
	}
	m, _ := strconv.Atoi(duo[1])
	if m == 0 {
		//var buff bytes.Buffer
		//buff.WriteString("Cuckoo")
		//for i := 1; i < h; i++ {
		//	buff.WriteString(" Cuckoo")
		//}
		//return buff.String()
		return strings.Repeat("Cuckoo ", h - 1) + "Cuckoo" // TIP: strings.Repeat()
	} else if m == 30 {
		return "Cuckoo"
	} else if m % 15 == 0 {
		return "Fizz Buzz"
	} else if m % 3 == 0 {
		return "Fizz"
	} else if m % 5 == 0 {
		return "Buzz"
	} else {
		return "tick"
	}
}
