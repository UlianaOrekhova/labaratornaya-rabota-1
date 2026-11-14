package main

type StackData struct {
	items []int
}

func (s *StackData) Push(value int) {
	s.items = append(s.items, value)
}

func (s *StackData) Pop() (int, bool) {
	if len(s.items) == 0 {
		return 0, false
	}
	value := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return value, true
}

func (s *StackData) Values() []int {
	out := make([]int, len(s.items))
	copy(out, s.items)
	return out
}

func (s *StackData) Load(data []int) {
	s.items = make([]int, len(data))
	copy(s.items, data)
}
