package main

import (
	"../../algorithm/shuffle"
	"fmt"
	"sort"
)

func main() {
	cards := shuffle.MakePlayingCards()
	fmt.Println(len(cards))
	sort.Sort(cards)

	shuffle.Shuffle(cards)
	//for i, v := range cards {
	//	fmt.Printf("%s %d\n", shuffle.SuitCharDict[v.Suit], v.Number)
	//	if (i+1)%17 == 0 {
	//		fmt.Println("-----------------------------------------------")
	//	}
	//}
	//fmt.Println("######################")
	player1 := cards[:17]
	player2 := cards[17:34]
	player3 := cards[34:]

	sort.Sort(sort.Reverse(player1))
	sort.Sort(sort.Reverse(player2))
	sort.Sort(sort.Reverse(player3))

	player1.Display()
	player2.Display()
	player3.Display()
}
