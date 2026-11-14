package main

import (
	"fmt"
	"strings"
)

type DNode struct {
	Item int
	Next *DNode
	Prev *DNode
}

type DSpisok struct {
	head *DNode
	tail *DNode
	a    int
}

func NewDSpisok() *DSpisok {
	return &DSpisok{}
}

func (d *DSpisok) findNode(value int) *DNode {
	for current := d.head; current != nil; current = current.Next {
		if current.Item == value {
			return current
		}
	}
	return nil
}

func (d *DSpisok) PushFront(value int) {
	newNode := &DNode{Item: value, Next: d.head}
	if d.head != nil {
		d.head.Prev = newNode
	} else {
		d.tail = newNode
	}
	d.head = newNode
	d.a++
}

func (d *DSpisok) PushBack(value int) {
	newNode := &DNode{Item: value, Prev: d.tail}
	if d.tail != nil {
		d.tail.Next = newNode
	} else {
		d.head = newNode
	}
	d.tail = newNode
	d.a++
}

func (d *DSpisok) InsertBefore(target, value int) bool {
	current := d.findNode(target)
	if current == nil {
		return false
	}
	if current == d.head {
		d.PushFront(value)
		return true
	}
	newNode := &DNode{Item: value, Next: current, Prev: current.Prev}
	current.Prev.Next = newNode
	current.Prev = newNode
	d.a++
	return true
}

func (d *DSpisok) InsertAfter(target, value int) bool {
	current := d.findNode(target)
	if current == nil {
		return false
	}
	if current == d.tail {
		d.PushBack(value)
		return true
	}
	newNode := &DNode{Item: value, Next: current.Next, Prev: current}
	current.Next.Prev = newNode
	current.Next = newNode
	d.a++
	return true
}

func (d *DSpisok) EraseValue(value int) bool {
	current := d.findNode(value)
	if current == nil {
		return false
	}
	if current.Prev != nil {
		current.Prev.Next = current.Next
	} else {
		d.head = current.Next
	}
	if current.Next != nil {
		current.Next.Prev = current.Prev
	} else {
		d.tail = current.Prev
	}
	d.a--
	return true
}

func (d *DSpisok) EraseAt(index int) (int, bool) {
	if index < 0 || index >= d.a {
		return 0, false
	}
	var current *DNode
	if index < d.a/2 {
		current = d.head
		for i := 0; i < index; i++ {
			current = current.Next
		}
	} else {
		current = d.tail
		for i := d.a - 1; i > index; i-- {
			current = current.Prev
		}
	}
	value := current.Item
	if current.Prev != nil {
		current.Prev.Next = current.Next
	} else {
		d.head = current.Next
	}
	if current.Next != nil {
		current.Next.Prev = current.Prev
	} else {
		d.tail = current.Prev
	}
	d.a--
	return value, true
}

func (d *DSpisok) EraseHead() (int, bool) {
	return d.EraseAt(0)
}

func (d *DSpisok) EraseTail() (int, bool) {
	return d.EraseAt(d.a - 1)
}

func (d *DSpisok) EraseBefore(target int) (int, bool) {
	current := d.findNode(target)
	if current == nil || current.Prev == nil {
		return 0, false
	}
	removed := current.Prev
	value := removed.Item
	current.Prev = removed.Prev
	if removed.Prev != nil {
		removed.Prev.Next = current
	} else {
		d.head = current
	}
	d.a--
	return value, true
}

func (d *DSpisok) EraseAfter(target int) (int, bool) {
	current := d.findNode(target)
	if current == nil || current.Next == nil {
		return 0, false
	}
	removed := current.Next
	value := removed.Item
	current.Next = removed.Next
	if removed.Next != nil {
		removed.Next.Prev = current
	} else {
		d.tail = current
	}
	d.a--
	return value, true
}

func (d *DSpisok) GetAt(index int) (int, bool) {
	if index < 0 || index >= d.a {
		return 0, false
	}
	var current *DNode
	if index < d.a/2 {
		current = d.head
		for i := 0; i < index; i++ {
			current = current.Next
		}
	} else {
		current = d.tail
		for i := d.a - 1; i > index; i-- {
			current = current.Prev
		}
	}
	return current.Item, true
}

func (d *DSpisok) Contains(value int) bool {
	return d.findNode(value) != nil
}

func (d *DSpisok) WriteValues(out *strings.Builder) {
	for current := d.head; current != nil; current = current.Next {
		fmt.Fprintf(out, " %d", current.Item)
	}
}
