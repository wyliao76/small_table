import { describe, it, expect } from "vitest"

interface IPlayer {
    id: number
    name: string
}

interface ISeat {
    sit(player: IPlayer): boolean
    un_sit(): boolean
    get_player(): IPlayer | null
    is_empty(): boolean
}

interface ITable {
    add_player(player: IPlayer, index: number): number
    remove_player(player: IPlayer, index: number): number
    get_player(index: number): IPlayer | null
}

class Player implements IPlayer {
    constructor(
        public id: number,
        public name: string,
    ) {}
}

class Seat implements ISeat {
    constructor(private player: IPlayer | null) {}

    sit = (player: IPlayer): boolean => {
        if (this.player === null) {
            this.player = player
            return true
        }
        return false
    }

    un_sit = (): boolean => {
        if (this.player) {
            this.player = null
            return true
        }
        return false
    }

    get_player = (): IPlayer | null => {
        return this.player
    }

    is_empty = (): boolean => {
        return this.player === null
    }
}

// the table has 4 seats only
class Table implements ITable {
    static NUM_OF_SEATS = 4
    private seats: ISeat[]

    constructor() {
        this.seats = []
        for (let i = 0; i < Table.NUM_OF_SEATS; ++i) {
            this.seats.push(new Seat(null))
        }
    }

    is_full = (): boolean => {
        for (const seat of this.seats) {
            if (seat.is_empty()) {
                return false
            }
        }
        return true
    }

    add_player = (player: IPlayer, index: number): number => {
        // check index
        if (index >= Table.NUM_OF_SEATS) {
            return -2
        }

        // check full
        if (this.is_full()) {
            return -1
        }

        // check duplicate
        for (let i = 0; i < Table.NUM_OF_SEATS; ++i) {
            if (this.seats[i].get_player()?.id === player.id) {
                return -3
            }
        }

        // seat is not free
        if (!this.seats[index].is_empty()) {
            for (let i = 0; i < Table.NUM_OF_SEATS; ++i) {
                if (this.seats[i].is_empty()) {
                    index = i
                    break
                }
            }
        }
        // seat is free
        this.seats[index].sit(player)
        return index
    }

    remove_player = (player: IPlayer, index: number): number => {
        // check index
        if (index >= Table.NUM_OF_SEATS) {
            return -2
        }

        // check if seated
        if (this.seats[index].get_player() === null) {
            return -1
        }
        // check if same player
        if (this.seats[index].get_player()?.id !== player.id) {
            return -3
        }

        this.seats[index].un_sit()
        return 0
    }

    get_player = (index: number): IPlayer | null => {
        if (index >= Table.NUM_OF_SEATS) {
            return null
        }
        return this.seats[index].get_player()
    }
}

describe("Table of 4", () => {
    const table = new Table()
    const players = Array.from(
        { length: 8 },
        (v, i) => new Player(i, String(i)),
    )

    it("player 0 takes seat 2, should return 2. FreeMap is 1011(11).", () => {
        expect(table.add_player(players[0], 2)).toBe(2)
    })

    it("player 1 takes seat 0, should return 0, FreeMap is 1010(10).", () => {
        expect(table.add_player(players[1], 0)).toBe(0)
    })

    it("duplicate player 1 takes seat 1, should return -3, FreeMap is 1010(10)", () => {
        expect(table.add_player(players[1], 1)).toBe(-3)
    })

    it("player 2 takes seat 3, should return 3, FreeMap is 0010(2).", () => {
        expect(table.add_player(players[2], 3)).toBe(3)
    })

    it("player 3 takes seat 0, should return remaining seat 1, FreeMap is 0000.", () => {
        expect(table.add_player(players[3], 0)).toBe(1)
    })

    it("player 4 takes seat 0, should return -1, FreeMap is 0000.", () => {
        expect(table.add_player(players[4], 0)).toBe(-1)
    })

    it("player 4 takes seat 4, should return -2, FreeMap is 0000.", () => {
        expect(table.add_player(players[4], 4)).toBe(-2)
    })

    it("remove player 2 from seat 2, should return -3.", () => {
        expect(table.remove_player(players[2], 2)).toBe(-3)
    })

    it("remove player 2 from seat 4, should return -2", () => {
        expect(table.remove_player(players[2], 4)).toBe(-2)
    })

    it("remove player 0 from seat 2, should return 0, FreeMap is 0100(4)", () => {
        expect(table.remove_player(players[0], 2)).toBe(0)
    })

    it("remove player 0 from seat 2, should return -1.", () => {
        expect(table.remove_player(players[0], 2)).toBe(-1)
    })

    it("player 4 takes seat 0, should return 2, FreeMap is 0.", () => {
        expect(table.add_player(players[4], 0)).toBe(2)
    })

    it("check who seats at seat 4, should return null.", () => {
        expect(table.get_player(4)).toBeNull()
    })

    it("check who seats at seat 2, should return player 4.\n", () => {
        expect(table.get_player(2)).toBe(players[4])
    })
})
