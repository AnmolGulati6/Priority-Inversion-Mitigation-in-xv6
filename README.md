
# Priority Inversion Mitigation in xv6

## Introduction
In this project, we explore priority inversion within the xv6 operating system, extending it with mechanisms to mitigate its effects. Priority inversion occurs when a higher-priority task is delayed by a lower-priority task holding a shared resource. To address this, we implement a user-space sleep lock, a nice system call, and modify the scheduler to prioritize processes based on their nice values.

## Objectives
- Understand priority inversion and priority inheritance.
- Implement a user-space sleep lock.
- Develop a nice system call to adjust process priorities.
- Modify the scheduler to consider process nice values.

## Background
Priority inversion occurs when a higher-priority task is delayed by a lower-priority task holding a shared resource. Priority inheritance is a solution where the priority of the lower-priority task is temporarily elevated to that of the highest-priority waiting task.

## Project Details
- **User-space Sleep Lock:** Implement a mutex structure and associated functions for user-space locks.
- **Nice System Call:** Implement the nice system call to adjust process priorities.
- **Scheduler Modification:** Modify the scheduler to consider process nice values for task prioritization.
- **Priority Inheritance:** Implement priority inheritance in the scheduler to prevent priority inversion.

## License
This project is licensed under the [License Name] License - see the LICENSE.md file for details.
```
