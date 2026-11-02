# Car Sales System (C)

A menu-driven command-line program for a car dealership, written in C.

## Features

- **View stock**: 3 models (M4 Competition, G63, Porsche 911) across 4 model years, sorted newest first
- **Buy cars**: input validation, stock checks, purchase confirmation and a 10% Car Club member discount
- **Sales report**: every sale with customer, model, year and price, plus units sold and revenue per model
- **Star ratings and feedback**: customers rate their purchase and leave written feedback
- **Persistent data**: sales and stock are saved to binary files with `fwrite`/`fread`, so data survives restarts

## Concepts used

Structs, 2D arrays, bubble sort, file I/O, string handling and defensive input validation.

## Build and run

```bash
cc -Wall -o carsales main.c
./carsales
```

To reset the shop, delete `sale_data.txt` and `car_stocks.txt`.

Built as part of my BEng Computer Science Engineering at Anglia Ruskin University (2025).
