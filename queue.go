package main

type QueueData struct {
	items []int
}

func (q *QueueData) Push(value int) {
	q.items = append(q.items, value)
}

func (q *QueueData) Pop() (int, bool) {
	if len(q.items) == 0 {
		return 0, false
	}
	value := q.items[0]
	q.items = q.items[1:]
	return value, true
}

func (q *QueueData) Values() []int {
	out := make([]int, len(q.items))
	copy(out, q.items)
	return out
}

func (q *QueueData) Load(data []int) {
	q.items = make([]int, len(data))
	copy(q.items, data)
}
