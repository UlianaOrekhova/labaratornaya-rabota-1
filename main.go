package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Database struct {
	Arrays      map[string]*ArrayData
	SinglyLists map[string]*SSpisok
	DoublyLists map[string]*DSpisok
	Stacks      map[string]*StackData
	Queues      map[string]*QueueData
	Trees       map[string]*FullTree
}

func newDatabase() *Database {
	return &Database{
		Arrays:      make(map[string]*ArrayData),
		SinglyLists: make(map[string]*SSpisok),
		DoublyLists: make(map[string]*DSpisok),
		Stacks:      make(map[string]*StackData),
		Queues:      make(map[string]*QueueData),
		Trees:       make(map[string]*FullTree),
	}
}

// getOrCreate — эмуляция поведения map::operator[] в C++
func getArray(db *Database, name string) *ArrayData {
	if v, ok := db.Arrays[name]; ok {
		return v
	}
	v := &ArrayData{}
	db.Arrays[name] = v
	return v
}

func getSList(db *Database, name string) *SSpisok {
	if v, ok := db.SinglyLists[name]; ok {
		return v
	}
	v := NewSSpisok()
	db.SinglyLists[name] = v
	return v
}

func getDList(db *Database, name string) *DSpisok {
	if v, ok := db.DoublyLists[name]; ok {
		return v
	}
	v := NewDSpisok()
	db.DoublyLists[name] = v
	return v
}

func getStack(db *Database, name string) *StackData {
	if v, ok := db.Stacks[name]; ok {
		return v
	}
	v := &StackData{}
	db.Stacks[name] = v
	return v
}

func getQueue(db *Database, name string) *QueueData {
	if v, ok := db.Queues[name]; ok {
		return v
	}
	v := &QueueData{}
	db.Queues[name] = v
	return v
}

func getTree(db *Database, name string) *FullTree {
	if v, ok := db.Trees[name]; ok {
		return v
	}
	v := &FullTree{}
	db.Trees[name] = v
	return v
}

// writeValues — общий вариант для среза int
func writeValuesSlice(out *strings.Builder, values []int) {
	for _, v := range values {
		fmt.Fprintf(out, " %d", v)
	}
}

func printValuesSlice(values []int) {
	var sb strings.Builder
	writeValuesSlice(&sb, values)
	printValuesStr(sb.String())
}

func printValuesStr(s string) {
	if s == "" {
		fmt.Println("-> (empty)")
	} else {
		fmt.Println("->" + s)
	}
}

func printResult(result bool) {
	if result {
		fmt.Println("-> TRUE")
	} else {
		fmt.Println("-> FALSE")
	}
}

func loadData(fileName string, db *Database) {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return
	}
	lines := strings.Split(string(data), "\n")
	for _, line := range lines {
		fields := strings.Fields(line)
		if len(fields) < 2 {
			continue
		}
		typ := fields[0]
		name := fields[1]
		nums := fields[2:]
		switch typ {
		case "M":
			item := getArray(db, name)
			for _, s := range nums {
				if v, err := strconv.Atoi(s); err == nil {
					item.PushBack(v)
				}
			}
		case "F":
			item := getSList(db, name)
			for _, s := range nums {
				if v, err := strconv.Atoi(s); err == nil {
					item.PushBack(v)
				}
			}
		case "L":
			item := getDList(db, name)
			for _, s := range nums {
				if v, err := strconv.Atoi(s); err == nil {
					item.PushBack(v)
				}
			}
		case "S":
			item := getStack(db, name)
			for _, s := range nums {
				if v, err := strconv.Atoi(s); err == nil {
					item.Push(v)
				}
			}
		case "Q":
			item := getQueue(db, name)
			for _, s := range nums {
				if v, err := strconv.Atoi(s); err == nil {
					item.Push(v)
				}
			}
		case "T":
			item := getTree(db, name)
			for _, s := range nums {
				if v, err := strconv.Atoi(s); err == nil {
					TreeInsert(item, v)
				}
			}
		}
	}
}

func saveData(fileName string, db *Database) error {
	var sb strings.Builder

	for name, item := range db.Arrays {
		sb.WriteString("M " + name)
		writeValuesSlice(&sb, item.Values())
		sb.WriteString("\n")
	}
	for name, item := range db.SinglyLists {
		sb.WriteString("F " + name)
		item.WriteValues(&sb)
		sb.WriteString("\n")
	}
	for name, item := range db.DoublyLists {
		sb.WriteString("L " + name)
		item.WriteValues(&sb)
		sb.WriteString("\n")
	}
	for name, item := range db.Stacks {
		sb.WriteString("S " + name)
		writeValuesSlice(&sb, item.Values())
		sb.WriteString("\n")
	}
	for name, item := range db.Queues {
		sb.WriteString("Q " + name)
		writeValuesSlice(&sb, item.Values())
		sb.WriteString("\n")
	}
	for name, item := range db.Trees {
		sb.WriteString("T " + name)
		TreeWrite(item, &sb)
		sb.WriteString("\n")
	}
	return os.WriteFile(fileName, []byte(sb.String()), 0644)
}

func printNamed(name string, db *Database) {
	if v, ok := db.Arrays[name]; ok {
		printValuesSlice(v.Values())
		return
	}
	if v, ok := db.SinglyLists[name]; ok {
		var sb strings.Builder
		v.WriteValues(&sb)
		printValuesStr(sb.String())
		return
	}
	if v, ok := db.DoublyLists[name]; ok {
		var sb strings.Builder
		v.WriteValues(&sb)
		printValuesStr(sb.String())
		return
	}
	if v, ok := db.Stacks[name]; ok {
		printValuesSlice(v.Values())
		return
	}
	if v, ok := db.Queues[name]; ok {
		printValuesSlice(v.Values())
		return
	}
	if v, ok := db.Trees[name]; ok {
		var sb strings.Builder
		TreeWrite(v, &sb)
		printValuesStr(sb.String())
		return
	}
	fmt.Println("-> Container not found")
}

func printHelp() {
	fmt.Println("MCREATE name, MPUSH name value, MINSERT name index value, MGET name index, MDEL name index, MSET name index value, MLEN name, MREAD name")
	fmt.Println("FPUSH/FTAIL name value, FHEAD name value, FBEFORE name target value, FAFTER name target value")
	fmt.Println("FDEL name value, FDELAT name index, FDELHEAD name, FDELTAIL name, FDELBEFORE name target, FDELAFTER name target, FGET name index, FFIND name value, FREAD name")
	fmt.Println("L commands work like F commands: LPUSH/LTAIL/LHEAD/LBEFORE/LAFTER/LDEL/LDELAT/LDELHEAD/LDELTAIL/LDELBEFORE/LDELAFTER/LGET/LFIND/LREAD")
	fmt.Println("SPUSH name value, SPOP name, SGET name, SREAD name; QPUSH name value, QPOP name, QGET name, QREAD name")
	fmt.Println("TINSERT name value, TGET name value, TFULL name, TREAD name, ISMEMBER name value, PRINT name, HELP, EXIT")
}

func atoi(s string) (int, bool) {
	v, err := strconv.Atoi(s)
	return v, err == nil
}

func execute(command string, db *Database) bool {
	fields := strings.Fields(command)
	if len(fields) == 0 {
		return false
	}
	op := fields[0]

	if op == "HELP" {
		printHelp()
		return false
	}
	if op == "PRINT" {
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		printNamed(fields[1], db)
		return false
	}

	changed := false

	switch op {
	case "MCREATE":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		name := fields[1]
		if _, ok := db.Arrays[name]; !ok {
			db.Arrays[name] = &ArrayData{}
			changed = true
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> EXISTS")
		}
		return changed

	case "MPUSH":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		getArray(db, name).PushBack(value)
		fmt.Println("-> OK")
		return true

	case "MINSERT":
		if len(fields) < 4 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		index, ok1 := atoi(fields[2])
		value, ok2 := atoi(fields[3])
		if !ok1 || !ok2 {
			fmt.Println("Invalid arguments")
			return false
		}
		if getArray(db, name).InsertAt(index, value) {
			fmt.Println("-> OK")
			return true
		}
		fmt.Println("-> Invalid index")
		return false

	case "MGET":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		index, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		if item, ok := db.Arrays[name]; ok {
			if v, ok := item.GetAt(index); ok {
				fmt.Printf("-> %d\n", v)
				return false
			}
		}
		fmt.Println("-> Invalid index or container")
		return false

	case "MDEL":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		index, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		if item, ok := db.Arrays[name]; ok {
			if v, ok := item.EraseAt(index); ok {
				fmt.Printf("-> %d\n", v)
				return true
			}
		}
		fmt.Println("-> Invalid index or container")
		return false

	case "MSET":
		if len(fields) < 4 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		index, ok1 := atoi(fields[2])
		value, ok2 := atoi(fields[3])
		if !ok1 || !ok2 {
			fmt.Println("Invalid arguments")
			return false
		}
		if item, ok := db.Arrays[name]; ok && item.SetAt(index, value) {
			fmt.Println("-> OK")
			return true
		}
		fmt.Println("-> Invalid index or container")
		return false

	case "MLEN":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		if item, ok := db.Arrays[fields[1]]; ok {
			fmt.Printf("-> %d\n", item.Length())
		} else {
			fmt.Println("-> 0")
		}
		return false

	case "MREAD":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		if item, ok := db.Arrays[fields[1]]; ok {
			printValuesSlice(item.Values())
		} else {
			fmt.Println("-> Container not found")
		}
		return false
	}

	// --- Односвязный список (F*) ---
	if strings.HasPrefix(op, "F") {
		changed = executeSList(op, fields, db)
		return changed
	}

	// --- Двусвязный список (L*) ---
	if strings.HasPrefix(op, "L") {
		changed = executeDList(op, fields, db)
		return changed
	}

	// --- Стек (S*) ---
	if strings.HasPrefix(op, "S") {
		changed = executeStack(op, fields, db)
		return changed
	}

	// --- Очередь (Q*) ---
	if strings.HasPrefix(op, "Q") {
		changed = executeQueue(op, fields, db)
		return changed
	}

	// --- Дерево (T* / ISMEMBER) ---
	if strings.HasPrefix(op, "T") || op == "ISMEMBER" {
		changed = executeTree(op, fields, db)
		return changed
	}

	fmt.Println("Unknown command. Enter HELP")
	return false
}

func executeSList(op string, fields []string, db *Database) bool {
	switch op {
	case "FPUSH", "FTAIL", "FHEAD", "FBEFORE", "FAFTER":
		if op == "FBEFORE" || op == "FAFTER" {
			if len(fields) < 4 {
				fmt.Println("Invalid arguments")
				return false
			}
			name := fields[1]
			target, ok1 := atoi(fields[2])
			value, ok2 := atoi(fields[3])
			if !ok1 || !ok2 {
				fmt.Println("Invalid arguments")
				return false
			}
			var result bool
			if op == "FBEFORE" {
				result = getSList(db, name).InsertBefore(target, value)
			} else {
				result = getSList(db, name).InsertAfter(target, value)
			}
			if result {
				fmt.Println("-> OK")
				return true
			}
			fmt.Println("-> Target not found")
			return false
		}
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		if op == "FHEAD" {
			getSList(db, name).PushFront(value)
		} else {
			getSList(db, name).PushBack(value)
		}
		fmt.Println("-> OK")
		return true

	case "FDEL", "FDELAT", "FDELHEAD", "FDELTAIL", "FDELBEFORE", "FDELAFTER":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		name := fields[1]
		item, ok := db.SinglyLists[name]
		if !ok {
			fmt.Println("-> Container not found")
			return false
		}
		var result bool
		var value int
		switch op {
		case "FDEL":
			if len(fields) < 3 {
				fmt.Println("Missing value")
				return false
			}
			v, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing value")
				return false
			}
			result = item.EraseValue(v)
		case "FDELAT":
			if len(fields) < 3 {
				fmt.Println("Missing index")
				return false
			}
			idx, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing index")
				return false
			}
			value, result = item.EraseAt(idx)
		case "FDELHEAD":
			value, result = item.EraseHead()
		case "FDELTAIL":
			value, result = item.EraseTail()
		case "FDELBEFORE":
			if len(fields) < 3 {
				fmt.Println("Missing target")
				return false
			}
			t, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing target")
				return false
			}
			value, result = item.EraseBefore(t)
		case "FDELAFTER":
			if len(fields) < 3 {
				fmt.Println("Missing target")
				return false
			}
			t, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing target")
				return false
			}
			value, result = item.EraseAfter(t)
		}
		if result {
			fmt.Printf("-> %d\n", value)
			return true
		}
		fmt.Println("-> Element not found")
		return false

	case "FGET", "FFIND", "FREAD":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		item, ok := db.SinglyLists[fields[1]]
		if !ok {
			fmt.Println("-> Container not found")
			return false
		}
		if op == "FREAD" {
			var sb strings.Builder
			item.WriteValues(&sb)
			printValuesStr(sb.String())
		} else if op == "FGET" {
			if len(fields) < 3 {
				fmt.Println("Missing index")
				return false
			}
			idx, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing index")
				return false
			}
			if v, ok := item.GetAt(idx); ok {
				fmt.Printf("-> %d\n", v)
			} else {
				fmt.Println("-> Invalid index")
			}
		} else {
			if len(fields) < 3 {
				fmt.Println("Missing value")
				return false
			}
			v, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing value")
				return false
			}
			printResult(item.Contains(v))
		}
		return false
	}
	return false
}

func executeDList(op string, fields []string, db *Database) bool {
	switch op {
	case "LPUSH", "LTAIL", "LHEAD", "LBEFORE", "LAFTER":
		if op == "LBEFORE" || op == "LAFTER" {
			if len(fields) < 4 {
				fmt.Println("Invalid arguments")
				return false
			}
			name := fields[1]
			target, ok1 := atoi(fields[2])
			value, ok2 := atoi(fields[3])
			if !ok1 || !ok2 {
				fmt.Println("Invalid arguments")
				return false
			}
			var result bool
			if op == "LBEFORE" {
				result = getDList(db, name).InsertBefore(target, value)
			} else {
				result = getDList(db, name).InsertAfter(target, value)
			}
			if result {
				fmt.Println("-> OK")
				return true
			}
			fmt.Println("-> Target not found")
			return false
		}
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		if op == "LHEAD" {
			getDList(db, name).PushFront(value)
		} else {
			getDList(db, name).PushBack(value)
		}
		fmt.Println("-> OK")
		return true

	case "LDEL", "LDELAT", "LDELHEAD", "LDELTAIL", "LDELBEFORE", "LDELAFTER":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		name := fields[1]
		item, ok := db.DoublyLists[name]
		if !ok {
			fmt.Println("-> Container not found")
			return false
		}
		var result bool
		var value int
		switch op {
		case "LDEL":
			if len(fields) < 3 {
				fmt.Println("Missing value")
				return false
			}
			v, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing value")
				return false
			}
			result = item.EraseValue(v)
		case "LDELAT":
			if len(fields) < 3 {
				fmt.Println("Missing index")
				return false
			}
			idx, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing index")
				return false
			}
			value, result = item.EraseAt(idx)
		case "LDELHEAD":
			value, result = item.EraseHead()
		case "LDELTAIL":
			value, result = item.EraseTail()
		case "LDELBEFORE":
			if len(fields) < 3 {
				fmt.Println("Missing target")
				return false
			}
			t, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing target")
				return false
			}
			value, result = item.EraseBefore(t)
		case "LDELAFTER":
			if len(fields) < 3 {
				fmt.Println("Missing target")
				return false
			}
			t, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing target")
				return false
			}
			value, result = item.EraseAfter(t)
		}
		if result {
			fmt.Printf("-> %d\n", value)
			return true
		}
		fmt.Println("-> Element not found")
		return false

	case "LGET", "LFIND", "LREAD":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		item, ok := db.DoublyLists[fields[1]]
		if !ok {
			fmt.Println("-> Container not found")
			return false
		}
		if op == "LREAD" {
			var sb strings.Builder
			item.WriteValues(&sb)
			printValuesStr(sb.String())
		} else if op == "LGET" {
			if len(fields) < 3 {
				fmt.Println("Missing index")
				return false
			}
			idx, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing index")
				return false
			}
			if v, ok := item.GetAt(idx); ok {
				fmt.Printf("-> %d\n", v)
			} else {
				fmt.Println("-> Invalid index")
			}
		} else {
			if len(fields) < 3 {
				fmt.Println("Missing value")
				return false
			}
			v, ok := atoi(fields[2])
			if !ok {
				fmt.Println("Missing value")
				return false
			}
			printResult(item.Contains(v))
		}
		return false
	}
	return false
}

func executeStack(op string, fields []string, db *Database) bool {
	switch op {
	case "SPUSH":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		getStack(db, name).Push(value)
		fmt.Println("-> OK")
		return true

	case "SPOP", "SGET", "SREAD":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		name := fields[1]
		item, ok := db.Stacks[name]
		if !ok {
			fmt.Println("-> Container not found")
			return false
		}
		switch op {
		case "SREAD":
			printValuesSlice(item.Values())
		case "SGET":
			vals := item.Values()
			if len(vals) == 0 {
				fmt.Println("-> Stack is empty")
			} else {
				fmt.Printf("-> %d\n", vals[len(vals)-1])
			}
		case "SPOP":
			if v, ok := item.Pop(); ok {
				fmt.Printf("-> %d\n", v)
				return true
			}
			fmt.Println("-> Stack is empty")
		}
		return false
	}
	return false
}

func executeQueue(op string, fields []string, db *Database) bool {
	switch op {
	case "QPUSH":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		getQueue(db, name).Push(value)
		fmt.Println("-> OK")
		return true

	case "QPOP", "QGET", "QREAD":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		name := fields[1]
		item, ok := db.Queues[name]
		if !ok {
			fmt.Println("-> Container not found")
			return false
		}
		switch op {
		case "QREAD":
			printValuesSlice(item.Values())
		case "QGET":
			vals := item.Values()
			if len(vals) == 0 {
				fmt.Println("-> Queue is empty")
			} else {
				fmt.Printf("-> %d\n", vals[0])
			}
		case "QPOP":
			if v, ok := item.Pop(); ok {
				fmt.Printf("-> %d\n", v)
				return true
			}
			fmt.Println("-> Queue is empty")
		}
		return false
	}
	return false
}

func executeTree(op string, fields []string, db *Database) bool {
	switch op {
	case "TINSERT":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		if TreeInsert(getTree(db, name), value) {
			fmt.Println("-> OK")
			return true
		}
		fmt.Println("-> EXISTS")
		return false

	case "TGET", "ISMEMBER":
		if len(fields) < 3 {
			fmt.Println("Invalid arguments")
			return false
		}
		name := fields[1]
		value, ok := atoi(fields[2])
		if !ok {
			fmt.Println("Invalid arguments")
			return false
		}
		item, exists := db.Trees[name]
		printResult(exists && TreeContains(item, value))
		return false

	case "TFULL", "TISFULL":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		if item, ok := db.Trees[fields[1]]; ok {
			printResult(TreeIsFull(item))
		} else {
			fmt.Println("-> Container not found")
		}
		return false

	case "TREAD":
		if len(fields) < 2 {
			fmt.Println("Missing container name")
			return false
		}
		if item, ok := db.Trees[fields[1]]; ok {
			var sb strings.Builder
			TreeWrite(item, &sb)
			printValuesStr(sb.String())
		} else {
			fmt.Println("-> Container not found")
		}
		return false
	}
	return false
}

func main() {
	fileName := "file.data"
	query := ""
	hasQuery := false

	args := os.Args[1:]
	for i := 0; i < len(args); i++ {
		switch args[i] {
		case "--file":
			if i+1 < len(args) {
				fileName = args[i+1]
				i++
			}
		case "--query":
			if i+1 < len(args) {
				query = args[i+1]
				hasQuery = true
				i++
			}
		case "--help":
			printHelp()
			return
		}
	}

	db := newDatabase()
	loadData(fileName, db)

	if hasQuery {
		if execute(query, db) {
			if err := saveData(fileName, db); err != nil {
				fmt.Println("Cannot write file")
			}
		}
	} else {
		fmt.Println("Data structures. Enter HELP to see commands.")
		scanner := bufio.NewScanner(os.Stdin)
		for {
			fmt.Print("> ")
			if !scanner.Scan() {
				break
			}
			command := scanner.Text()
			if command == "EXIT" {
				break
			}
			if execute(command, db) {
				if err := saveData(fileName, db); err != nil {
					fmt.Println("Cannot write file")
				}
			}
		}
	}

	for _, tree := range db.Trees {
		TreeClear(tree)
	}
}
