package naive

import (
	"math"
)

// TODO try list and vector for this task

func CartesianNeighborsDistance(_, _, r int) (result []float64) {
	set := make(map[int]bool)
	for i := 1; i <= r; i++ {
		i2 := i * i
		set[i2] = true
		for j := 1; j <= i; j++ {
			set[i2 + j*j] = true
		}
	}
	for k := range set {
		result = append(result, math.Sqrt(float64(k)))
	}
	return
}
