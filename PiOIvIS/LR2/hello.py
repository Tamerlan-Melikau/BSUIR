from experta import Fact, KnowledgeEngine, Rule, NOT, MATCH


class Symptom(Fact):
    """Patient symptom."""
    pass


class Diagnosis(Fact):
    """Diagnosis."""
    pass


class DiagnosisEngine(KnowledgeEngine):
    @Rule(NOT(Symptom(name='temperature')))
    def ask_temperature(self):
        value = input("Temperature (normal/elevated/high/unknown): ").strip().lower()
        self.declare(Symptom(name='temperature', value=value))

    @Rule(NOT(Symptom(name='cough')))
    def ask_cough(self):
        value = input("Cough (none/dry/wet/unknown): ").strip().lower()
        self.declare(Symptom(name='cough', value=value))

    @Rule(NOT(Symptom(name='runny_nose')))
    def ask_cold(self):
        value = input("Runny nose (no/yes/unknown): ").strip().lower()
        self.declare(Symptom(name='runny_nose', value=value))

    @Rule(
        Symptom(name='temperature', value='high'),
        Symptom(name='cough', value='dry') | Symptom(name='cough', value='wet'),
        Symptom(name='runny_nose', value='yes')
    )
    def flu(self):
        self.declare(Diagnosis(name='flu'))
        print("Presumptive diagnosis: flu")

    @Rule(
        Symptom(name='temperature', value='elevated'),
        Symptom(name='cough', value='dry') | Symptom(name='cough', value='wet'),
        Symptom(name='runny_nose', value='yes')
    )
    def orz(self):
        self.declare(Diagnosis(name='ARI'))
        print("Presumptive diagnosis: ARI")

    @Rule(
        Symptom(name='cough', value='dry') | Symptom(name='cough', value='wet'),
        Symptom(name='temperature', value='normal') | Symptom(name='temperature', value='unknown'),
        Symptom(name='runny_nose', value='no') | Symptom(name='runny_nose', value='unknown'),
        NOT(Diagnosis(name='flu')),
        NOT(Diagnosis(name='ARI'))
    )
    def isolated_cough(self):
        self.declare(Diagnosis(name='isolated_cough'))
        print("Cough without other pronounced symptoms. Additional diagnostics needed.")

    @Rule(
        Symptom(name='runny_nose', value='yes'),
        Symptom(name='temperature', value='normal') | Symptom(name='temperature', value='unknown'),
        Symptom(name='cough', value='no') | Symptom(name='cough', value='unknown'),
        NOT(Diagnosis(name='flu')),
        NOT(Diagnosis(name='ARI')),
        NOT(Diagnosis(name='isolated_cough'))
    )
    def rhinitis(self):
        self.declare(Diagnosis(name='rhinitis'))
        print("Probably mild rhinitis (runny nose without other symptoms).")

    @Rule(
        Symptom(name='temperature', value='normal'),
        Symptom(name='cough', value='no'),
        Symptom(name='runny_nose', value='no'),
        NOT(Diagnosis(name='flu')),
        NOT(Diagnosis(name='ARI')),
        NOT(Diagnosis(name='isolated_cough')),
        NOT(Diagnosis(name='rhinitis'))
    )
    def healthy(self):
        self.declare(Diagnosis(name='healthy'))
        print("You are probably healthy.")

    @Rule(
        Symptom(name='temperature', value=MATCH.t),
        Symptom(name='cough', value=MATCH.c),
        Symptom(name='runny_nose', value=MATCH.n),
        NOT(Diagnosis())
    )
    def unknown(self, t, c, n):
        print("Could not make an unambiguous diagnosis.")
        print(f"Entered symptoms: temperature={t}, cough={c}, runny_nose={n}")


if __name__ == "__main__":
    engine = DiagnosisEngine()
    engine.reset()
    engine.run()