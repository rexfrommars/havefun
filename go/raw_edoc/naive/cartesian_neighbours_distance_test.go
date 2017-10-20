package naive

import (
	"testing"
	"reflect"
)

func TestCartesianNeighborsDistance(t *testing.T) {
	expected := []float64 {1.0, 1.4142135624}
	if result := CartesianNeighborsDistance(0, 0, 1); reflect.DeepEqual(result, expected) {
		t.Error("unexpected result", result)
	}
}

