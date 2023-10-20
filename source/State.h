#pragma once

enum class TickValue{QUIT = -1, CONTINUE = 0, NEXTSTATE = 1};

class State{
public:
    virtual ~State() = default;
    virtual TickValue Tick() = 0;
};