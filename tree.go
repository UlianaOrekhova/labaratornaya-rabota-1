package main

import (
	"fmt"
	"strings"
)

type TNode struct {
	Item  int
	Left  *TNode
	Right *TNode
}

type FullTree struct {
	Root  *TNode
	Count int
}

func treeContainsNode(node *TNode, value int) bool {
	if node == nil {
		return false
	}
	if node.Item == value {
		return true
	}
	return treeContainsNode(node.Left, value) || treeContainsNode(node.Right, value)
}

func TreeContains(tree *FullTree, value int) bool {
	return treeContainsNode(tree.Root, value)
}

func TreeInsert(tree *FullTree, value int) bool {
	if TreeContains(tree, value) {
		return false
	}
	newNode := &TNode{Item: value}
	if tree.Root == nil {
		tree.Root = newNode
		tree.Count = 1
		return true
	}

	queue := []*TNode{tree.Root}
	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]
		if current.Left == nil {
			current.Left = newNode
			tree.Count++
			return true
		}
		queue = append(queue, current.Left)
		if current.Right == nil {
			current.Right = newNode
			tree.Count++
			return true
		}
		queue = append(queue, current.Right)
	}
	return false
}

func treeIsFullNode(node *TNode) bool {
	if node == nil {
		return true
	}
	if node.Left == nil && node.Right == nil {
		return true
	}
	if node.Left == nil || node.Right == nil {
		return false
	}
	return treeIsFullNode(node.Left) && treeIsFullNode(node.Right)
}

func TreeIsFull(tree *FullTree) bool {
	return treeIsFullNode(tree.Root)
}

func treeHeight(node *TNode) int {
	if node == nil {
		return 0
	}
	left := treeHeight(node.Left)
	right := treeHeight(node.Right)
	if left > right {
		return left + 1
	}
	return right + 1
}

func treeWriteLevel(node *TNode, level int, out *strings.Builder) {
	if node == nil {
		return
	}
	if level == 1 {
		fmt.Fprintf(out, " %d", node.Item)
	} else {
		treeWriteLevel(node.Left, level-1, out)
		treeWriteLevel(node.Right, level-1, out)
	}
}

func TreeWrite(tree *FullTree, out *strings.Builder) {
	height := treeHeight(tree.Root)
	for i := 1; i <= height; i++ {
		treeWriteLevel(tree.Root, i, out)
	}
}

func TreeClear(tree *FullTree) {
	tree.Root = nil
	tree.Count = 0
}
