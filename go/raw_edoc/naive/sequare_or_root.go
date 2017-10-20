package naive

import "math"
import "fmt"

func SquareOrSquareRoot(arr []int) []int{
	result := make([]int, len(arr))  // TIP: make int array with dynamic length
	fmt.Println(arr)
	for i, a := range arr {
		root := math.Sqrt(float64(a))
		tail := root - math.Floor(root)
		if tail == 0 {
			result[i] = int(math.Floor(root))
		} else {
			result[i] = a * a
			fmt.Println(i, arr[i])
		}
	}
	fmt.Println(arr)
	return result
}
