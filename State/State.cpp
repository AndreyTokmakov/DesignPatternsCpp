/**============================================================================
Name        : IState.cpp
Created on  : 27.11.2022
Author      : Tokmakov Andrey
Version     : 1.0
Copyright   : Your copyright notice
Description : IState
============================================================================**/

#include "State.h"

#include <iostream>
#include <string_view>
#include <memory>
#include <utility>
#include <optional>
#include <variant>

namespace State::ClimateControl
{

    class IState {
    public:
        [[nodiscard]]
        virtual std::string GetName() const noexcept = 0;

        virtual void Freeze(std::shared_ptr<class StateContext> context) = 0;
        virtual void Heat(std::shared_ptr<class StateContext> context) = 0;

        virtual ~IState() = default;
    };


    class State : public IState {
    private:
        std::string name;
    public:
        explicit State(std::string name): name(std::move(name)) {
        }

        [[nodiscard]]
        std::string GetName() const noexcept override  {
            return this->name;
        }
    };



    class StateContext : public std::enable_shared_from_this<StateContext>{
    private:
        std::unique_ptr<IState> state;

    public:
        explicit StateContext(std::unique_ptr<IState> state);
        virtual ~StateContext();

    public:
        void Freeze();
        void Heat();
        void SetState(std::unique_ptr<IState> state) noexcept;
        std::unique_ptr<IState> GetState() noexcept;
    };


    class SolidState : public State {
    public:
        SolidState();
        void Freeze(std::shared_ptr<StateContext> context) override;
        void Heat(std::shared_ptr<StateContext> context) override;
    };


    class LiquidState : public State {
    public:
        LiquidState();
        void Freeze(std::shared_ptr<StateContext> context) override;
        void Heat(std::shared_ptr<StateContext> context) override;
    };


    class GasState : public State {
    public:
        GasState();
        void Freeze(std::shared_ptr<StateContext> context) override;
        void Heat(std::shared_ptr<StateContext> context) override;
    };


    StateContext::StateContext(std::unique_ptr<IState> state):
            state(state.release()) {
    }

    void StateContext::Freeze() {
        std::cout << "Freezing " << state->GetName() << "..." << std::endl;
        this->state->Freeze(this->shared_from_this());
    }

    void StateContext::Heat() {
        std::cout << "Heating " << state->GetName() << "..." << std::endl;
        this->state->Heat(this->shared_from_this());
    }

    void StateContext::SetState(std::unique_ptr<IState> st) noexcept {
        std::cout << "Changing state from " << this->state->GetName() << " to " << st->GetName() << "..." << std::endl;
        this->state = std::move(st);
    }

    std::unique_ptr<IState> StateContext::GetState() noexcept {
        return std::move(this->state);
    }

    StateContext::~StateContext() {
        std::cout << "Destroying stata " << this->state->GetName() << std::endl;
    }


    /** SolidState class: **/
    SolidState::SolidState() : State("Solid") {
    }

    void SolidState::Freeze([[maybe_unused]] std::shared_ptr<StateContext> context) {
        std::cout << "Nothing happens" << std::endl;
    }

    void SolidState::Heat(std::shared_ptr<StateContext> context) {
        context->SetState(std::make_unique<LiquidState>());
    }


    /** LiquidState class: **/
    LiquidState::LiquidState(): State("Liquid") {
    }

    void LiquidState::Freeze(std::shared_ptr<StateContext> context) {
        context->SetState(std::make_unique<SolidState>());
    }

    void LiquidState::Heat(std::shared_ptr<StateContext> context) {
        context->SetState(std::make_unique<GasState>());
    }


    /** GasState class: **/
    GasState::GasState() : State("Gas")  {
    }

    void GasState::Freeze(std::shared_ptr<StateContext> context) {
        context->SetState(std::make_unique<LiquidState>());
    }

    void GasState::Heat([[maybe_unused]] std::shared_ptr<StateContext> context) {
        std::cout << "Nothing happens" << std::endl;
    }

    void Test()
    {
        std::shared_ptr<StateContext> sc = std::make_shared<StateContext>(std::make_unique<SolidState>());
        sc->Heat();
        sc->Heat();
        sc->Heat();
        sc->Freeze();
        sc->Freeze();
        sc->Freeze();
    }
}

namespace State::TCPStateMachine
{
    enum class Event {
        connect,
        connected,
        disconnect,
        timeout
    };

    inline std::ostream &operator<<(std::ostream &os, const Event event) {
        switch (event) {
            case Event::connect: os << "connect"; break;
            case Event::connected: os << "connected"; break;
            case Event::disconnect: os << "disconnect"; break;
            case Event::timeout: os << "timeout"; break;
        }
        return os;
    }

    struct IState {
        virtual std::unique_ptr<IState> onEvent(Event event) = 0;

        [[nodiscard]]
        virtual std::string getName() const  = 0;

        virtual ~IState() = default;
    };

    /** States: **/
    struct Idle : IState {
        std::unique_ptr<IState> onEvent(Event event) override;

        [[nodiscard]]
        std::string getName() const override;
    };

    struct Connecting : IState {
        std::unique_ptr<IState> onEvent(Event event) override;

        [[nodiscard]]
        std::string getName() const override;

    private:
        uint32_t                    m_trial = 0;
        static constexpr uint8_t    m_max_trial = 3;
    };

    struct Connected : IState {
        std::unique_ptr<IState> onEvent(Event e) override;

        [[nodiscard]]
        std::string getName() const override;
    };




    std::unique_ptr<IState> Idle::onEvent(Event event) {
        std::cout << getName() << " ==> " << event;
        if (Event::connect == event)
            return std::make_unique<Connecting>();
        return nullptr;
    }

    std::string Idle::getName() const {
        return {"Idle"};
    }

    std::unique_ptr<IState> Connecting::onEvent(Event event)
    {
        std::cout << getName() << " ==> " << event;
        switch (event) {
            case Event::connected:
                return std::make_unique<Connected>();
                break;
            case Event::timeout:
                return ++m_trial < m_max_trial ? nullptr : std::make_unique<Idle>();
                break;
            case Event::connect:
                [[fallthrough]];
            case Event::disconnect:
                return nullptr;
                break;
        }
        return nullptr;
    }

    std::string Connecting::getName() const {
        return {"Connecting"};
    }

    std::unique_ptr<IState> Connected::onEvent(Event event)
    {
        std::cout << getName() << " ==> " << event;
        if (Event::disconnect == event)
            return std::make_unique<Idle>();
        return nullptr;
    }

    std::string Connected::getName() const {
        return {"Connected"};
    }

    struct Bluetooth
    {
        std::unique_ptr<IState> state = std::make_unique<Idle>();

        void dispatch(Event e)
        {
            auto stateNew = state->onEvent(e);
            if (stateNew)
                state = std::move(stateNew);

            std::cout << " ==> " << state->getName() << std::endl;
        }

        template <typename... Events>
        void establish_connection(Events... e) {
            (dispatch(e), ...);
        }
    };

    void Test()
    {
        Bluetooth bl;
        bl.establish_connection(Event::connect, Event::timeout, Event::connected, Event::disconnect);
    }
};

namespace State::TCPStateMachine_Visitor
{
    struct EventConnect { std::string m_address; };
    struct EventConnected { };
    struct EventDisconnect { };
    struct EventTimeout { };

    using Event = std::variant<EventConnect,EventConnected, EventDisconnect, EventTimeout>;

    struct Idle { };

    struct Connecting {
        std::string                 m_address;
        uint32_t                    m_trial = 0;
        static constexpr uint8_t    m_max_trial = 3;
    };
    struct Connected { };

    using State = std::variant<Idle, Connecting, Connected>;


    struct TransitionsHandler
    {
        std::optional<State> operator()(Idle&, const EventConnect &e) {
            std::cout << "Idle -> Connect" << std::endl;
            return Connecting{e.m_address};
        }

        std::optional<State> operator()(Connecting&, const EventConnected &) {
            std::cout << "Connecting -> Connected" << std::endl;
            return Connected{};
        }

        std::optional<State> operator()(Connecting &s, const EventTimeout &) {
            std::cout << "Connecting -> Timeout" << std::endl;
            return ++s.m_trial < Connecting::m_max_trial ? std::nullopt : std::optional<State>(Idle{});
        }

        std::optional<State> operator()(Connected&, const EventDisconnect &) {
            std::cout << "Connected -> Disconnect" << std::endl;
            return Idle{};
        }

        template <typename State_t, typename Event_t>
        std::optional<State> operator()(State_t &, const Event_t &) const {
            std::cout << "Unknown" << std::endl;
            return std::nullopt;
        }
    };

    template <typename StateVariant, typename EventVariant, typename Transitions>
    struct Bluetooth {
        StateVariant currentState;

        void dispatch(const EventVariant &event)
        {
            std::optional<StateVariant> new_state = visit(Transitions{}, currentState, event);
            if (new_state)
                currentState = *std::move(new_state);
        }

        template <typename... Events>
        void establish_connection(Events... e) {
            (dispatch(e), ...);
        }
    };

    void Test()
    {
        Bluetooth<State, Event, TransitionsHandler> bl;
        bl.establish_connection(EventConnect{"AA:BB:CC:DD"},
                                EventTimeout{},
                                EventConnected{},
                                EventDisconnect{});
    }
}



void State::TestAll()
{
    ClimateControl::Test();

    // TCPStateMachine::Test();

    // TCPStateMachine_Visitor::Test();
}

