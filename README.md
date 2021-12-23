# Caro-NP-project

First, create the following folders:
1. build/
2. exec/
3. test/

## Folder Tree
The folder organization should look like this:

```text
.
├── LICENSE
├── Makefile
├── README.md
├── build
├── exec
├── src
│   ├── Client_side
│   │   ├── client_chat.c
│   │   ├── client_console.c
│   │   ├── client_helper.c
│   │   ├── client_helper.h
│   │   └── tcp_client.c
│   ├── Server_side
│   │   ├── Database
│   │   │   ├── Accounts
│   │   │   │   ├── admin123.profile
│   │   │   │   └── all.ranking
│   │   │   └── Users.csv
│   │   ├── Functions
│   │   │   ├── chat.c
│   │   │   ├── hist.c
│   │   │   ├── list.c
│   │   │   ├── play.c
│   │   │   ├── setname.c
│   │   │   └── sign_in_up.c
│   │   ├── Game
│   │   │   ├── caro_main.c
│   │   │   ├── game.c
│   │   │   ├── game.h
│   │   │   ├── game_tree.c
│   │   │   └── player.c
│   │   ├── Gameplays
│   │   │   ├── gameplay.c
│   │   │   └── gameplay.h
│   │   ├── Users
│   │   │   ├── test_user.c
│   │   │   ├── user.c
│   │   │   ├── user.h
│   │   │   └── utils.c
│   │   ├── server_helper.c
│   │   ├── server_helper.h
│   │   └── tcp_server.c
│   └── Utils
│       ├── data.h
│       ├── error.c
│       ├── error.h
│       ├── logger.c
│       ├── logger.h
│       ├── message.c
│       ├── message.h
│       └── types.h
└── test
```

## How to run code
1. Run Makefile with:
```bash
make clean
make
```
2. Run server
```bash
./exec/server
```
3. Run client
```bash
./exec/client
```

## Config the code
