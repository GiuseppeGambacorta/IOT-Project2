# Relazione del Progetto-2 
## Design
### Relazione tra Sheduler e Task
Il design globale del progetto si basa su di una architettura a `Task` amministrate da uno `Scheduler` che le amminaistra sulla dase dei loro periodi base.

```mermaid
classDiagram
    class Scheduler {
        - int basePeriod
        - int nTasks
        - Task* taskList[MAX_TASKS]
        - SchedulerTimer timer
        + Scheduler()
        + void init(int basePeriod)
        + bool addTask(Task* task)
        + void schedule()
        + Task** getTaskList()
        + int getNumTask()
        + Task* getTask(int index)
    }

    class Task {
        # int myPeriod
        # int timeElapsed
        # bool active
        + void init(int period)
        + virtual void tick() = 0
        + bool updateAndCheckTime(int basePeriod)
        + bool isActive()
        + void setActive(bool active)
        + virtual void reset() = 0
    }

    Scheduler --> Task : manages
```

#### Dettagli del Diagramma:
1. `Scheduler`:
   - Ha una relazione con `Task` tramite l'array `taskList`, che può contenere fino a `MAX_TASKS` oggetti `Task`.
   - Invoca i metodi delle istanze di `Task` attraverso il metodo `schedule`.
2. `Task`:
   - Interfaccia base contenete i metodi `tick` e `reset`, essi verrano implementati delle specifiche task.

### Interoperatività delle Task
Le task `InputTask`, `WasteDisposalTask`, `StdExecTask`, `AlarmLevelTask`, `AlarmTempTask`, e `OutputTask` sono implementazioni della classe astratta `Task`. Esse sono contenute nella `taskList` dello `Scheduler` e chiamate da quest'ultimo sulla base del loro stato di attività. Lo stato di attività delle task `StdExecTask`, `AlarmLevelTask` e `AlarmTempTask` è amministrato dalla task di menagment `WasteDisposalTask`

```mermaid
classDiagram
    class Task {
        <<abstract>>
        # int myPeriod
        # int timeElapsed
        # bool active
        + void init(int period)
        + virtual void tick() = 0
        + bool updateAndCheckTime(int basePeriod)
        + bool isActive()
        + void setActive(bool active)
        + virtual void reset() = 0
    }

    class InputTask {
        - Sonar& levelDetector
        - Pir& userDetector
        - TemperatureSensor& tempSensor
        - DigitalInput& openButton
        - DigitalInput& closeButton
        + InputTask(Sonar&, Pir&, TemperatureSensor&, DigitalInput&, DigitalInput&)
        + void tick()
        + void reset()
    }

    class WasteDisposalTask {
        - StdExecTask& stdExecTask
        - AlarmLevelTask& alarmLevelTask
        - AlarmTempTask& alarmTempTask
        - Sonar& levelDetector
        - TemperatureSensor& tempSensor
        - WasteDisposalState state
        + WasteDisposalTask(StdExecTask&, AlarmLevelTask&, AlarmTempTask&, Sonar&, TemperatureSensor&)
        + void tick()
        + void reset() 
    }

    class StdExecTask {
        - StdExecState state
        - Door& door
        - Display& display
        - DigitalInput& openButton
        - DigitalInput& closeButton
        - DigitalOutput& ledGreen
        - DigitalOutput& ledRed
        - Pir& userDetector
        + StdExecTask(Door&, Display&, DigitalInput&, DigitalInput&, DigitalOutput&, DigitalOutput&, Pir&)
        + void tick()
        + void reset()
    }

    class AlarmLevelTask {
        - State state
        - Door& door
        - Display& display
        - DigitalOutput& ledGreen
        - DigitalOutput& ledRed
        - Sonar& levelDetector
        + AlarmLevelTask(Door&, Display&, DigitalOutput&, DigitalOutput&, Sonar&)
        + void tick()
        + void reset()
    }

    class AlarmTempTask {
        - State state
        - DigitalOutput& ledGreen
        - DigitalOutput& ledRed
        - Display& display
        - Door& door
        - TemperatureSensor& tempSensor
        + AlarmTempTask(DigitalOutput&, DigitalOutput&, Display&, Door&, TemperatureSensor&)
        + void tick()
        + void reset()
    }

    class OutputTask {
        - Door& door
        - Display& display
        - DigitalOutput& ledGreen
        - DigitalOutput& ledRed
        + OutputTask(Door&, Display&, DigitalOutput&, DigitalOutput&)
        + void tick()
        + void reset()
    }

    class SerialInputTask {
        - SerialManager& serialManager
        + SerialInputTask()
        + void tick()
        + void reset()
    }

    class SerialOutputTask {
        - SerialManager& serialManager
        + SerialOutputTask()
        + void tick()
        + void reset()
    }

    %% Inheritance Relationships
    SerialInputTask --|> Task 
    SerialOutputTask --|> Task
    Task <|-- InputTask
    Task <|-- WasteDisposalTask
    Task <|-- StdExecTask
    Task <|-- AlarmLevelTask
    Task <|-- AlarmTempTask
    Task <|-- OutputTask


    %% Dependency Relationships
    WasteDisposalTask --> StdExecTask : setActive
    WasteDisposalTask --> AlarmLevelTask : setActive
    WasteDisposalTask --> AlarmTempTask : setActive
```

#### Dettagli del Diagramma:
1. **Ereditarietà**:
   - Tutte le task derivano dalla classe astratta `Task`.

2. **Dipendenze**:
   - `WasteDisposalTask` gestisce le sotto-task (`StdExecTask`, `AlarmLevelTask`, `AlarmTempTask`) e utilizza componenti come `Sonar` e `TemperatureSensor`.
   - `InputTask` legge sensori come `Sonar`, `Pir`, `TemperatureSensor` e interagisce con gli input digitali.
   - Altre task (es. `AlarmLevelTask`, `AlarmTempTask`) controllano output (es. LED, display) e interagiscono con i sensori o attuatori (es. `Door`, `Sonar`, `TemperatureSensor`).
   - `SerialInputTask` e `SerialOutputTask` dipendono da `SerialManager` e lo utilizzano per gestire le operazioni seriali.

## Specifiche delle Task

### InputTask
La `InputTask` viene chiamata dallo `Scheduler` come prima task e sfrutta il metodo `update` contenuto negli oggetti di input per aggiornarne il valore. Grazie a questo passaggio, abbiamo la sicurezza che le task successivamente schedulate lavoreranno sempre sugli stessi dati per il resto del periodo dello `Scheduler`.

### WasteDisposalTask
La `WasteDisposalTask` è la task che si occupa della gestione delle task `StdExecTask`, `AlarmLevelTask` e `AlarmTempTask`. Grazie alla sua azione attiva e disattiva queste ultime permettendo la gestione dei casi critici.

```mermaid

stateDiagram-v2
    [*] --> STD_EXEC

    STD_EXEC: Standard Execution
    LVL_ALLARM: Level Alarm
    TEMP_ALLARM: Temperature Alarm

    STD_EXEC --> LVL_ALLARM : level <= maxLevel
    STD_EXEC --> TEMP_ALLARM : temp >= maxTemp && tempTimer.isTimeElapsed() == true

    LVL_ALLARM --> STD_EXEC : emptyButton.isActive() == true

    TEMP_ALLARM --> STD_EXEC : restoreButton.isActive() == true

```

### StdExecTask
La `StdExecTask` si propone di modellare la macchina a stati finiti che rappresenta le operazioni compibili dal bidone in assenza di condizioni critiche.

```mermaid
stateDiagram-v2
    [*] --> READY
    
    READY: Ready
    OPEN: Open
    SLEEP: Sleep

    READY --> OPEN : openButton.isActive()
    READY --> SLEEP : !userDetector.isDetected() && userTimer.isTimeElapsed()

    OPEN --> READY : closeButton.isActive() || closeTimer.isTimeElapsed()
    
    SLEEP --> READY : userDetector.isDetected()
```

### AllarmLevelTask
L'`AlarmLevelTask` modella la gestione della criticità legata al riempimento del bidone.

```mermaid
stateDiagram-v2
    [*] --> IDLE

    IDLE: Idle
    ALARM: Alarm
    EMPTY: Empty
    RESET: Reset

    IDLE --> ALARM : level <= maxLevel
    ALARM --> EMPTY : emptyButton.isActive() == true
    EMPTY --> RESET : timer.isTimeElapsed()
    RESET --> IDLE
```

### AllarmTempTask
L'`AlarmTempTask` modella la gestione di un raggiungimento critico di temperatura.

```mermaid
stateDiagram-v2
    [*] --> IDLE

    IDLE: Idle
    ALARM: Alarm
    RESET: Reset

    IDLE --> ALARM : level <= maxLevel
    ALARM --> RESET : temp >= maxTemp && tempTimer.isTimeElapsed() == true
    RESET --> IDLE
```

### OutputTask
La `OuputTask` viene chiamata dallo `Scheduler` come ultima task e sfrutta il metodo `update` contenuto negli oggetti di output per aggiornarne lo stato a livello hardware in un unico momento dello schedul.