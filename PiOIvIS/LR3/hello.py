from kanren import Relation, facts, run, var, conde

employee = Relation()
kpi_level = Relation()
tasks_level = Relation()
has_violation = Relation()
bonus_eligible = Relation()
bonus_standard = Relation()
bonus_high = Relation()

facts(employee,
    ("Tamerlan",),
    ("Anna",),
    ("Ivan",),
    ("Olga",),
    ("Peter",),
    ("Maria",),
    ("Sergey",)
)

facts(kpi_level,
    ("Tamerlan", "excellent"),
    ("Anna", "excellent"),
    ("Ivan", "high"),
    ("Olga", "low"),
    ("Peter", "high"),
    ("Maria", "excellent"),
    ("Sergey", "high")
)

facts(tasks_level,
    ("Tamerlan", "high"),  
    ("Anna", "high"),
    ("Ivan", "medium"),
    ("Olga", "low"),
    ("Peter", "medium"),
    ("Maria", "high"),
    ("Sergey", "medium")
)

facts(has_violation,
    ("Ivan", "lateness"),
    ("Olga", "error in report")
)

def rule_kpi_ok(emp):
    return conde(
        (kpi_level(emp, "high"),),
        (kpi_level(emp, "excellent"),)
    )

def rule_tasks_ok(emp):
    return conde(
        (tasks_level(emp, "medium"),),
        (tasks_level(emp, "high"),)
    )

def rule_kpi_excellent(emp):
    return conde((kpi_level(emp, "excellent"),))

def rule_tasks_high(emp):
    return conde((tasks_level(emp, "high"),))

def is_eligible(emp):
    kpi_ok = len(run(0, var(), kpi_level(emp, "high"))) > 0 or len(run(0, var(), kpi_level(emp, "excellent"))) > 0
    tasks_ok = len(run(0, var(), tasks_level(emp, "medium"))) > 0 or len(run(0, var(), tasks_level(emp, "high"))) > 0
    no_viol = len(run(0, var(), has_violation(emp, var()))) == 0
    return kpi_ok and tasks_ok and no_viol

def bonus_level(emp):
    kpi_ok = len(run(0, var(), kpi_level(emp, "high"))) > 0 or len(run(0, var(), kpi_level(emp, "excellent"))) > 0
    tasks_ok = len(run(0, var(), tasks_level(emp, "medium"))) > 0 or len(run(0, var(), tasks_level(emp, "high"))) > 0
    no_viol = len(run(0, var(), has_violation(emp, var()))) == 0
    kpi_excellent = len(run(0, var(), kpi_level(emp, "excellent"))) > 0
    tasks_high = len(run(0, var(), tasks_level(emp, "high"))) > 0
    
    if not (kpi_ok and tasks_ok and no_viol):
        return 0
    if kpi_excellent and tasks_high:
        return 2
    return 1

def get_violations(emp):
    viol_var = var()
    results = run(0, viol_var, has_violation(emp, viol_var))
    violations_list = []
    for item in results:
        if hasattr(item, 'value'):
            violations_list.append(item.value)
        else:
            violations_list.append(str(item))
    return violations_list

employees = ["Tamerlan", "Anna", "Ivan", "Olga", "Peter", "Maria", "Sergey"]

print("Query 1: employees who passed basic criteria (kpi>=80, tasks>=8, no violations)")
for emp in employees:
    if is_eligible(emp):
        print(f"  {emp}")

print("\n")
print("Query 2: employees with high bonus (kpi>90 and tasks>=12)")
for emp in employees:
    if bonus_level(emp) == 2:
        print(f"  {emp}")

print("\n")
print("Query 3: employees with violations")
for emp in employees:
    violations = get_violations(emp)
    if violations:
        print(f"  {emp}: {violations}")

print("\n")
print("Query 4: detailed analysis for each employee")
for emp in employees:
    kpi_lvl_result = run(1, var(), kpi_level(emp, var()))
    kpi_lvl = kpi_lvl_result[0] if kpi_lvl_result else "unknown"
    if hasattr(kpi_lvl, 'value'):
        kpi_lvl = kpi_lvl.value
    
    tasks_lvl_result = run(1, var(), tasks_level(emp, var()))
    tasks_lvl = tasks_lvl_result[0] if tasks_lvl_result else "unknown"
    if hasattr(tasks_lvl, 'value'):
        tasks_lvl = tasks_lvl.value
    
    has_viol = len(run(0, var(), has_violation(emp, var()))) > 0
    level = bonus_level(emp)
    
    print(f"\n{emp}:")
    print(f"  kpi level: {kpi_lvl}")
    print(f"  tasks level: {tasks_lvl}")
    print(f"  violations: {'yes' if has_viol else 'no'}")
    
    if level == 2:
        print(f"  bonus: high")
    elif level == 1:
        print(f"  bonus: standard")
    else:
        print(f"  bonus: none")