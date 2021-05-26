# Design of Mastimer v1.0 

## 结构设计

![image-20210513195802023](C:\Users\10849\AppData\Roaming\Typora\typora-user-images\image-20210513195802023.png)

## 类设计

`Todo` 用于描述一个任务，包含名称、三参数、已用时间、预计时间。以结构体形式呈现。

任务列表直接用 `QVector<Todo>`，不做单独的类

`Controller` 提供用户行为需要的所有方法

## 用户行为

![image-20210514183213557](C:\Users\10849\AppData\Roaming\Typora\typora-user-images\image-20210514183213557.png)

### 番茄操作

`begin new pomo` 检查当前 `pomoFlag=0` 时令 `pomoFlag=1` 并记录 `pomoStartTime`

`commit pomo` 检查当前 `pomoFlag=1` 并且 `currentTime-pomoStartTime>minimalPomoLength`，检查 `pctlTodolist` 中有合法选项，读出选项 ID 并修改 `m_todolist` 中状态，最后提醒成功，并设置 `pomoFlag=0`，并重绘 `pctlTodolist`

`destory pomo` 检查当前 `pomoFlag=1` 并提醒用户确认，若确认，则 `pomoFlag=0`

### 任务操作

`pctlShuffle` 点击时，对 `m_todolist` 中每个元素重新生成优先因子，并排序

每次 `pctlTodolist` 中选项发生修改时，要更新下方 `pctlTodoName, pctlTodoUsed, pctlTodoTotal, pctlTodoWeight, pctlTodoUrgency, pctlTodoFocus, pctlDeleteTodo` 状态：如果没有选中则直接禁用，否则启用，并将修改内容

`pctlTodoName, pctlTodoUsed, pctlTodoTotal, pctlTodoWeight, pctlTodoUrgency, pctlTodoFocus` 中任何一个内容发生修改时，要同步修改 `m_todolist` 中的值，并重绘 `pctlTodolist`

pctlAddTodo 点击时，会自动产生一个新的 Todo

`pctlDeleteTodo` 点击时，询问用户是否确认，若确认则从 `m_todolist` 中删除该项，并重绘 `pctlTodolist`

## 模块设计

`pctlTodoName, pctlTodoUsed, pctlTodoTotal, pctlTodoWeight, pctlTodoUrgency` 只要做一个值同步的功能即可，所以不单独设计类

`pctlDeleteTodo` 只需要调用一个申请删除的函数即可，这个函数放在 `Controller` 类中实现

`pctlTodolist`  只需要负责显示 `m_todolist` 的内容并返回当前选择什么即可，也不单独成类

`pctlPomoBegin, pctlPomoCommit, pctlPommoDestroy` 只需要调用 `Controller` 类中提供的函数即可

`pctlPomoStatus` 由一个定时器控制，不断从 `Controller` 接口提供的函数中获取当前番茄状态

## 接口设计

### Todo 类

这是一个结构体，`public` 成员有 `name,weight,urgency,focus,used,total`，包含 `private` 成员 `randfactor`

提供成员函数 `generateRandomFactor()`，重新生成一个 `randfactor`

提供成员函数 `double Evaluation()`，返回根据公式计算出的优先级（`Controller` 会根据这个优先级对 `todo` 进行重排序）

### Controller 类

Controller 类包含 `private` 成员 `m_todolist, pomoFlag, pomoStartTime`

提供成员 `bool PomoBegin()`

提供成员 `bool PomoCommit(int nId)`

提供成员 `bool PomoDestroy()`

提供成员 `QString PomoStatus()`

提供成员 `void ShuffleTodolist()`

提供成员 `Todo& GetTodo(int nId)`

提供成员 `void AddTodo(int nId)`

提供成员 `void DeleteTodo(int nId)`