## Goal

This is a project extended from one of the interview questions I have encountered.
The question was to write a table of 4 seats which can be sit by players.
Need to prevent duplicate players in a table and show OOP.

For OOP we have separation of concern so table, seat, player are three classes.
Seat manages sit and un_sit and holds a player. Table holds 4 seats.

To find if a table is full,
we iterate the seat array and ask the seats if it's taken.
If all seats are taken then the table is full, return an error.

Next, to find if a player has already seated at this table,
we iterate and ask the seats if current player exists.
If exists we return duplicate player error.

Next we try to sit the current player, if taken we iterate to next, else we sit the player.

# This is a simple and easy to code example for OOP.
# However, I wanted to explore the practical design instead of just doing OOP.

First, the Seat class can be abstracted away as an array in the Table.
We can store player (pointer) or player_id in this seats array.

Second, I want a way to track if a table is full or not.
We can use an int for counting how many players or use the array size.

Finally, I need to find a way to store the status of seats, which seats are taken and which are free.
We can also consider using set for the seats to de-duplicate.

However, with my experience in C I start thinking about how would this be implemented in high level languages.
I don't like dynamic array because it would be an array with realloc or tree.
Set will probably be a HashSet.
In this case I know how many seats a table has, so I prefer a fixed size array.
HashSet sounds nice, but the overhead makes it a bad choice.
I don't want to use more cpu (hashing) and memory (sparse) for an array of 4.

# So let's use a fixed size array for player pointer.
# If we use array's index to represent the seat numbers, we can also store the seat's status.
# We check duplication by iterating through the array since it's small and spatial locality should help.
# For the table is full feature, we use an int to track how many player.
# Then we iterate to find a free seat when needed.

That's how much I can think of initially with mostly Javascript and a bit of C.
Later I wanted to do it in C and see what I can discover.

## First I did a design for small scale like a local game of 1 table. I assumed memory is a constraint.

I can use player pointers like OOP would do, and this uses 8 bytes per pointer.
So 4 * 8 = 32 bytes. We can iterate and check duplication and fullness.
Or use 1 byte to store how many players.

# So 32 + 1 = 33 bytes.

I have also considered using player_id, range from 0 to 3, each takes 1 byte to store.
So 4 bytes only, and 1 byte for player number.
However, 0 is a player_id and can't be used as null. I need something to track the status of seats.
The 1 byte for player number is uint8_t which ranges from 0 to 255, but it only tracks the player number.
If I add something else I need more memory.

### Then I discovered bitmap.

A bitmap is consecutive bits that we use to store information.
1 is set, meaning the seat is free. 0 is clear, meaning the seat is taken.
Since it uses bitwise operation for computers it would be fast.
It can be used to check if a seat is taken, if table is full and to find a free seat.

# This design use 5 bytes. (4 for player_id array and 1 for bitmap)

We can even push it to 2 bytes by storing each player_id in 2 bits.
Therefore, 1 byte for player_id array and 1 byte for bitmap.

Usually memory is not so scarce so we can use pointers and it is pretty flexible.
Bitmap is a nice addition to track player number and to find a free slot.

## So my second step is to explore a bigger game with many tables and players on one machine.

We use pointer for players and tables. Each table has a bitmap.
This should work for most time.
However, I recalled that my option instructor said if we want to scale even more,
pointers are not good because they are local to a machine.
That means if we need more computers this won't work.

## Finally, distributed system.

So we are back to array and index. Array can be mapped to a different machine.
It is also a great way to partition a fixed size of memory (Here is the players).
We can determine how many players and how many tables a server can have.
An index can be used and if we align it with binary (base 2) and it works like memory cache line I have learned in school.
We can perform right swift to find which partition and it's index on the partition.
it's also possible to recover should a partition fail because array is portable.

I intend to keep bitmap in my design and am still exploring.
I am also thinking about use 0 as null value which would simplify the business logic,
but it might ruin the math? We will lose Player_id, server_id, table_id 0.


To be continue...




# template-c Repository Guide

Welcome to the `c template` repository. This guide will help you set up and run the provided scripts.

## **Table of Contents**

1. [Cloning the Repository](#cloning-the-repository)
2. [Prerequisites](#Prerequisites)
3. [Running the `generate-cmakelists.sh` Script](#running-the-generate-cmakelistssh-script)
4. [Running the `change-compiler.sh` Script](#running-the-change-compilersh-script)
5. [Running the `build.sh` Script](#running-the-buildsh-script)
5. [Running the `build-all.sh` Script](#running-the-build-allsh-script)
6. [Copy the template to start a new project](#copy-the-template-to-start-a-new-project)

## **Cloning the Repository**

Clone the repository using the following command:

```bash
git clone https://github.com/programming101dev/template-c.git
```

Navigate to the cloned directory:

```bash
cd template-c
```

Ensure the scripts are executable:

```bash
chmod +x *.sh
```

## **Prerequisites**

- to ensure you have all of the required tools installed, run:
```bash
./check-env.sh
```

If you are missing tools follow these [instructions](https://docs.google.com/document/d/1ZPqlPD1mie5iwJ2XAcNGz7WeA86dTLerFXs9sAuwCco/edit?usp=drive_link).

## **Running the generate-cmakelists.sh Script**

You will need to create the CMakeLists.txt file:

```bash
./generate-cmakelists.sh
```

## **Running the change-compiler.sh Script**

Tell CMake which compiler you want to use:

```bash
./change-compiler.sh -c <compiler>
```

To the see the list of possible compilers:

```bash
cat supported_cxx_compilers.txt
```

## **Running the build.sh Script**

To build the program run:

```bash
./build.sh
```

## **Running the build-all.sh Script**

To build the program with all compilers run:

```bash
./build-all.sh
```

## **Copy the template to start a new project**

To create a new project from the template, run:

```bash
./copy-template.sh <desitnation directory>
```

This will copy all of the files needed to start a new project.

1. Edit the files.txt
2. run ./generate-cmakelists.sh
3. run ./change-compiler.sh -c <compiler>
4. run ./build.sh

The files.txt file contains:
<executable> <source files> <header files> <libraries>

When you need to add/removes files to/from the project you must rerun the 4 steps above. 
