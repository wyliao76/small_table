import { describe, it, expect } from "vitest"

interface IPlayer {
    id: number
    name: string
}

interface ITable {
    sit(player: IPlayer, index: number): number
    un_sit(player: IPlayer, index: number): number
    get_player(index: number): IPlayer | null
}

class Player implements IPlayer {
    constructor(
        public id: number,
        public name: string,
    ) {}
}

// the table has 4 seats only
class Table implements ITable {
    static NUM_OF_SEATS = 4
    private seats: (IPlayer | null)[] = Array(Table.NUM_OF_SEATS).fill(null)
    private freeMap: number = 0b1111

    get_seats = (): (IPlayer | null)[] => {
        return this.seats
    }

    get_freeMap = (): number => {
        return this.freeMap
    }

    is_full = (): boolean => {
        return this.freeMap === 0
    }

    sit = (player: IPlayer, index: number): number => {
        // validate index
        if (index >= Table.NUM_OF_SEATS) {
            return -2
        }

        // check if full
        if (this.is_full()) {
            return -1
        }

        // check duplicate
        for (let i = 0; i < Table.NUM_OF_SEATS; ++i) {
            if (!(this.freeMap & (1 << i)) && this.seats[i]?.id === player.id) {
                    return -3
            }
        }

        // if free
        if (this.freeMap & (1 << index)) {
            console.log(`The seat ${index} is free.`)
        } else {
            for (let i = 0; i < Table.NUM_OF_SEATS; ++i) {
                if (this.freeMap & (1 << i)) {
                    index = i
                    console.log(
                        `The seat ${index} was taken, allocate to seat ${i}.`,
                    )
                }
            }
        }
        // clear bit
        this.freeMap &= ~(1 << index)
        // add player
        this.seats[index] = player

        return index
    }

    un_sit = (player: IPlayer, index: number): number => {
        // validate input
        if (index >= Table.NUM_OF_SEATS) {
            return -2
        }

        // if seat was free
        if (this.freeMap & (1 << index)) {
            return -1
        }

        // validate player
        if (this.seats[index]?.id !== player.id) {
            return -3
        }

        // set the bit
        this.freeMap |= 1 << index

        // remove player
        this.seats[index] = null
        return 0
    }

    get_player(index: number): IPlayer | null {
        if (index >= Table.NUM_OF_SEATS) {
            return null
        }
        return this.seats[index]
    }
}

describe("Table of 4", () => {
    const table = new Table()
    const players = Array.from(
        { length: 8 },
        (v, i) => new Player(i, String(i)),
    )

    it("Should be 15", () => {
        expect(table.get_freeMap()).toBe(0b1111)
    })

    it("player 0 takes seat 2, should return 2. FreeMap is 1011(11).", () => {
        expect(table.sit(players[0], 2)).toBe(2)
        expect(table.get_freeMap()).toBe(0b1011)
    })

    it("player 1 takes seat 0, should return 0, FreeMap is 1010(10).", () => {
        expect(table.sit(players[1], 0)).toBe(0)
        expect(table.get_freeMap()).toBe(0b1010)
    })

    it("duplicate player 1 takes seat 1, should return -3, FreeMap is 1010(10)", () => {
        expect(table.sit(players[1], 0)).toBe(-3)
        expect(table.get_freeMap()).toBe(0b1010)
    })

    it("player 2 takes seat 3, should return 3, FreeMap is 0010(2).", () => {
        expect(table.sit(players[2], 3)).toBe(3)
        expect(table.get_freeMap()).toBe(0b0010)
    })

    it("player 3 takes seat 0, should return remaining seat 1, FreeMap is 0000.", () => {
        expect(table.sit(players[3], 0)).toBe(1)
        expect(table.get_freeMap()).toBe(0b0000)
    })

    it("player 4 takes seat 0, should return -1, FreeMap is 0000.", () => {
        expect(table.sit(players[4], 0)).toBe(-1)
        expect(table.get_freeMap()).toBe(0b0000)
    })

    it("player 4 takes seat 4, should return -2, FreeMap is 0000.", () => {
        expect(table.sit(players[4], 4)).toBe(-2)
        expect(table.get_freeMap()).toBe(0b0000)
    })

    it("remove player 2 from seat 2, should return -3.", () => {
        expect(table.un_sit(players[2], 2)).toBe(-3)
        expect(table.get_freeMap()).toBe(0b0000)
    })

    it("remove player 2 from seat 4, should return -2", () => {
        expect(table.un_sit(players[2], 4)).toBe(-2)
        expect(table.get_freeMap()).toBe(0b0000)
    })

    it("remove player 0 from seat 2, should return 0, FreeMap is 0100(4)", () => {
        expect(table.un_sit(players[0], 2)).toBe(0)
        expect(table.get_freeMap()).toBe(0b0100)
    })

    it("remove player 0 from seat 2, should return -1.", () => {
        expect(table.un_sit(players[0], 2)).toBe(-1)
        expect(table.get_freeMap()).toBe(0b0100)
    })

    it("player 4 takes seat 0, should return 2, FreeMap is 0.", () => {
        expect(table.sit(players[4], 0)).toBe(2)
        expect(table.get_freeMap()).toBe(0b0000)
    })

    it("check who seats at seat 4, should return null.", () => {
        expect(table.get_player(4)).toBeNull()
    })

    it("check who seats at seat 2, should return player 4.\n", () => {
        expect(table.get_player(2)).toBe(players[4])
    })
})
