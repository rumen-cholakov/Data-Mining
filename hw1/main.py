#! /usr/bin/python3.6
from functools import reduce
import sys

result = []

def solution(state, goal):
    for i in range(len(state)):
        if goal[i] != state[i]:
            return False
        
    return True

def move(index, zeroPos, state):
    newState = state[:]
    newState[zeroPos], newState[index] = newState[index], newState[zeroPos]
    return newState

def canMove(index, zeroPos, state):
    return (state[index] == 1 and (zeroPos == index + 1 or zeroPos == index + 2)) or (state[index] == 2 and (zeroPos == index - 1 or zeroPos == index - 2))

def zeroPosition(state):
    return state.index(0)

def allMoves(state):
    newArr = []
    zeroPos = zeroPosition(state)
    for index in range(len(state)):
        if canMove(index, zeroPos, state):
            newArr.append(move(index, zeroPos, state))

    return newArr

def dfs(state, goal):
    result.append(state)

    if solution(state ,goal):
        printResult(result)
        return True

    for move in allMoves(state):
        if dfs(move, goal):
            return True
    
    result.remove(state)
    return False

def constructList(size):
    left = [1 for i in range(int(size))]
    right = [2 for i in range(int(size))]
    goal = right + [0] + left
    start = left + [0] + right

    return (start, goal)

def printResult(input):
    for step in input:
        print(''.join(map(str, step)).replace('1', '>').replace('2', '<').replace('0', '_'))

def main():
    size = sys.argv[1]

    (start, end) = constructList(size)
    dfs(start, end)

if __name__ == '__main__':
    main()