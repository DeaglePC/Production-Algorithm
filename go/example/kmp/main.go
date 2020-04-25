package main

import (
	"../../algorithm/kmp"
)

func main() {
	s := "abcdefg123456789ab123abcabdddabcabcabab123cdsdfascdab123abab123"
	p := "abcabdddabcabc"
	res := kmp.NewKMP(&s, &p).Match()
	for _, v := range res {
		println(v)
	}
}
