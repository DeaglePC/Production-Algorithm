package kmp

type KMP struct {
	next    []int
	source  *string
	pattern *string
}

func NewKMP(source, pattern *string) *KMP {
	return &KMP{
		next:    make([]int, len(*pattern)),
		source:  source,
		pattern: pattern,
	}
}

func (k *KMP) buildNext() {
	k.next[0] = 0
	// left pointer and right pointer for pattern
	for lp, rp := 0, 1; rp < len(*k.pattern); {
		if (*k.pattern)[lp] == (*k.pattern)[rp] {
			lp++
			k.next[rp] = lp
			rp++
		} else if lp != 0 {
			lp = k.next[lp-1]
		} else {
			k.next[rp] = lp // 0
			rp++
		}
	}
	//println("==========")
	//for _, v := range k.next {
	//	println(v)
	//}
	//println("==========")
}

func (k *KMP) search() []int {
	res := make([]int, 0)
	// source pointer, pattern pointer
	for sp, pp := 0, 0; sp < len(*k.source); {
		if (*k.source)[sp] == (*k.pattern)[pp] {
			sp++
			pp++
		} else if pp != 0 {
			pp = k.next[pp-1]
		} else {
			sp++
		}

		if pp == len(*k.pattern) {
			res = append(res, sp-pp+1) // save the first matched position
			pp = k.next[pp-1]
		}
	}
	return res
}

func (k *KMP) Match() []int {
	if len(*k.pattern) > len(*k.source) {
		return nil
	}

	k.buildNext()
	return k.search()
}
