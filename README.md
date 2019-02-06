Groceries Insight
=================

[![Build Status](https://travis-ci.org/ChrisVesters/GroceriesInsight.svg?branch=master)](https://travis-ci.org/ChrisVesters/GroceriesInsight)

## Introduction
Groceries Insight is an application meant to keep track of all your groceries.

## Goal
The main purpose of the application is to simply track and trace expenditure, and bying history.
However also additional information such as calorie information, usage can be tracked as well.
This will allow for more interesting insights such as the price/kcal.
The actual portion size (compared to the package specified).

## How To Build
cmake .
make

### Dependencies
ncurses: libncurses5-dev

## How To Run
Currently there is a hard dependency on the existance of the following files:
- output/products.json
	"products": {
		size": "0"
	}
- output/transactions.json
	"transactions": {
		"size": "0"
	}

If these files doe not exist, the application will crash.
