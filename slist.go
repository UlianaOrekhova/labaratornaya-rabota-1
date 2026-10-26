package main

import (
	"fmt"
	"strings"
)

type Node struct {
	Item int
	Next *Node
}

type SSpisok struct {
	head *Node
	tail *Node
	a    int
}

func NewSSpisok() *SSpisok {
	return &SSpisok{}
}

func (s *SSpisok) findNode(value int) *Node {
	for current := s.head; current != nil; current = current.Next {
		if current.Item == value {
			return current
		}
	}
	return nil
}

func (s *SSpisok) PushFront(value int) {
	newNode := &Node{Item: value, Next: s.head}
	s.head = newNode
	if s.tail == nil {
		s.tail = newNode
	}
	s.a++
}

func (s *SSpisok) PushBack(value int) {
	newNode := &Node{Item: value}
	if s.head == nil {
		s.head = newNode
		s.tail = newNode
	} else {
		s.tail.Next = newNode
		s.tail = newNode
	}
	s.a++
}

func (s *SSpisok) InsertBefore(target, value int) bool {
	current := s.findNode(target)
	if current == nil {
		return false
	}
	if current == s.head {
		s.PushFront(value)
		return true
	}
	x := s.head
	for x.Next != current {
		x = x.Next
	}
	newNode := &Node{Item: value, Next: current}
	x.Next = newNode
	s.a++
	return true
}

func (s *SSpisok) InsertAfter(target, value int) bool {
	current := s.findNode(target)
	if current == nil {
		return false
	}
	newNode := &Node{Item: value, Next: current.Next}
	current.Next = newNode
	if s.tail == current {
		s.tail = newNode
	}
	s.a++
	return true
}

func (s *SSpisok) EraseValue(value int) bool {
	var x *Node
	current := s.head
	for current != nil && current.Item != value {
		x = current
		current = current.Next
	}
	if current == nil {
		return false
	}
	if x == nil {
		s.head = current.Next
	} else {
		x.Next = current.Next
	}
	if s.tail == current {
		s.tail = x
	}
	s.a--
	return true
}

func (s *SSpisok) EraseAt(index int) (int, bool) {
	if index < 0 || index >= s.a {
		return 0, false
	}
	var x *Node
	current := s.head
	for i := 0; i < index; i++ {
		x = current
		current = current.Next
	}
	value := current.Item
	if x == nil {
		s.head = current.Next
	} else {
		x.Next = current.Next
	}
	if s.tail == current {
		s.tail = x
	}
	s.a--
	return value, true
}

func (s *SSpisok) EraseHead() (int, bool) {
	return s.EraseAt(0)
}

func (s *SSpisok) EraseTail() (int, bool) {
	return s.EraseAt(s.a - 1)
}

func (s *SSpisok) EraseBefore(target int) (int, bool) {
	current := s.findNode(target)
	if current == nil || current == s.head {
		return 0, false
	}
	var beforeX *Node
	x := s.head
	for x.Next != current {
		beforeX = x
		x = x.Next
	}
	value := x.Item
	if beforeX == nil {
		s.head = current
	} else {
		beforeX.Next = current
	}
	s.a--
	return value, true
}

func (s *SSpisok) EraseAfter(target int) (int, bool) {
	current := s.findNode(target)
	if current == nil || current.Next == nil {
		return 0, false
	}
	removed := current.Next
	value := removed.Item
	current.Next = removed.Next
	if s.tail == removed {
		s.tail = current
	}
	s.a--
	return value, true
}

func (s *SSpisok) GetAt(index int) (int, bool) {
	if index < 0 || index >= s.a {
		return 0, false
	}
	current := s.head
	for i := 0; i < index; i++ {
		current = current.Next
	}
	return current.Item, true
}

func (s *SSpisok) Contains(value int) bool {
	return s.findNode(value) != nil
}

func (s *SSpisok) WriteValues(out *strings.Builder) {
	for current := s.head; current != nil; current = current.Next {
		fmt.Fprintf(out, " %d", current.Item)
	}
}
