package main

type ArrayData struct {
	items []int
}

func (a *ArrayData) PushBack(value int) {
	a.items = append(a.items, value)
}

func (a *ArrayData) InsertAt(index, value int) bool {
	if index < 0 || index > len(a.items) {
		return false
	}
	a.items = append(a.items, 0)
	copy(a.items[index+1:], a.items[index:])
	a.items[index] = value
	return true
}

func (a *ArrayData) GetAt(index int) (int, bool) {
	if index < 0 || index >= len(a.items) {
		return 0, false
	}
	return a.items[index], true
}

func (a *ArrayData) EraseAt(index int) (int, bool) {
	if index < 0 || index >= len(a.items) {
		return 0, false
	}
	value := a.items[index]
	a.items = append(a.items[:index], a.items[index+1:]...)
	return value, true
}

func (a *ArrayData) SetAt(index, value int) bool {
	if index < 0 || index >= len(a.items) {
		return false
	}
	a.items[index] = value
	return true
}

func (a *ArrayData) Length() int {
	return len(a.items)
}

func (a *ArrayData) Values() []int {
	// возвращаем копию, как в C++ (values() возвращает по значению)
	out := make([]int, len(a.items))
	copy(out, a.items)
	return out
}

func (a *ArrayData) Load(data []int) {
	a.items = make([]int, len(data))
	copy(a.items, data)
}
