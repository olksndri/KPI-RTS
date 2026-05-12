class Task:
    def __init__(self, name, release, cost, deadline):
        self.name = name
        self.r = release  # Час появи
        self.c = cost  # Час виконання
        self.d_rel = deadline  # Відносний дедлайн
        self.d_abs = release + deadline  # Абсолютний дедлайн
        self.remaining = cost


def simulate_edf(tasks_data, preemptive=True, total_time=42):
    tasks = [Task(*data) for data in tasks_data]
    schedule = []
    current_task = None

    print(
        f"\n--- Моделювання EDF ({'з витісненням' if preemptive else 'без витіснення'}) ---"
    )

    for t in range(total_time):
        # Отримуємо список задач, що вже з'явилися і не завершені
        ready_tasks = [task for task in tasks if task.r <= t and task.remaining > 0]

        if ready_tasks:
            # Сортуємо за найближчим абсолютним дедлайном
            ready_tasks.sort(key=lambda x: x.d_abs)

            if preemptive:
                current_task = ready_tasks[0]
            else:
                if current_task is None or current_task.remaining == 0:
                    current_task = ready_tasks[0]

            schedule.append(current_task.name)
            current_task.remaining -= 1

            # Перевірка дедлайну
            if t + 1 > current_task.d_abs:
                print(
                    f"[УВАГА] Задача {current_task.name} порушила дедлайн у t={t + 1}"
                )
        else:
            schedule.append("-")

    # Візуалізація розкладу
    for task_name in sorted(list(set([d[0] for d in tasks_data]))):
        line = "".join([task_name[1] if x == task_name else "." for x in schedule])
        print(f"{task_name}: {line}")
    return schedule


# Дані варіанта №6: (Назва, r, C, D)
variant_6 = [("A1", 0, 12, 30), ("A2", 2, 14, 34), ("A3", 5, 6, 42), ("A4", 4, 10, 16)]

simulate_edf(variant_6, preemptive=False)
simulate_edf(variant_6, preemptive=True)
