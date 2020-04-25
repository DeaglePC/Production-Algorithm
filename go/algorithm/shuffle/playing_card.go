package shuffle

import (
	"fmt"
	"math/rand"
	"time"
)

type Suit uint8

const (
	Spade   Suit = iota // 黑桃
	Heart               // 红桃
	Diamond             // 方块
	Club                // 梅花
	Joker1              // 小王
	Joker2              // 大王
)

var SuitCharDict = map[Suit]string{
	Spade:   "♠",
	Heart:   "♥",
	Diamond: "♦",
	Club:    "♣",
	Joker1:  "x",
	Joker2:  "d",
}

const (
	MinNumber uint8 = 1
	MaxNumber       = 13
)

type PlayingCard struct {
	Number  uint8
	Suit    Suit
	Weights uint8
}

type PlayingCards []PlayingCard

func (p PlayingCards) Len() int {
	return len(p)
}

func (p PlayingCards) Less(i, j int) bool {
	return p[i].Weights < p[j].Weights
}

func (p PlayingCards) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

func (p PlayingCards) Display() {
	for _, v := range p {
		fmt.Printf("%s%02d ", SuitCharDict[v.Suit], v.Number)
	}
	fmt.Println()
}

func makeBySuit(suit Suit) PlayingCards {
	cards := make([]PlayingCard, 0, MaxNumber)

	for i := MinNumber; i <= MaxNumber; i++ {
		cards = append(cards, PlayingCard{Number: i, Suit: suit})
	}

	cards[1].Weights = MaxNumber
	cards[0].Weights = MaxNumber - 1

	for i := 2; i < len(cards); i++ {
		cards[i].Weights = uint8(i - 1)
	}

	return cards
}

func MakePlayingCards() PlayingCards {
	cards := make([]PlayingCard, 0, 4*MaxNumber+2)

	cards = append(cards, PlayingCard{Suit: Joker1, Weights: MaxNumber + 1})
	cards = append(cards, PlayingCard{Suit: Joker2, Weights: MaxNumber + 2})
	cards = append(cards, makeBySuit(Spade)...)
	cards = append(cards, makeBySuit(Heart)...)
	cards = append(cards, makeBySuit(Diamond)...)
	cards = append(cards, makeBySuit(Club)...)

	return cards
}

func Shuffle(cards PlayingCards) {
	for i := len(cards) - 1; i >= 0; i-- {
		rand.Seed(time.Now().Unix())
		ri := rand.Intn(i + 1)
		cards[i], cards[ri] = cards[ri], cards[i]
	}
}
