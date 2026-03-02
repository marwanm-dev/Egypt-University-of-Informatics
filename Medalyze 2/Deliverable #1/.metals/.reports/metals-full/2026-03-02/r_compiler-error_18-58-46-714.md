file://<HOME>/projects/Egypt-University-of-Informatics/Medalyze%202/Deliverable%20%231/medalyze/src/main/java/com/medalyze/Main.java
### java.util.NoSuchElementException: next on empty iterator

occurred in the presentation compiler.

presentation compiler configuration:


action parameters:
uri: file://<HOME>/projects/Egypt-University-of-Informatics/Medalyze%202/Deliverable%20%231/medalyze/src/main/java/com/medalyze/Main.java
text:
```scala
package com.medalyze;

import java.time.LocalDate;
import java.time.LocalTime;

public class Main {

    public static void main(String[] args) {

        Patient patient = new Patient("P1", "Marwan", "0100000000");
        Doctor doctor = new Doctor("D1", "Cardiology");

        Appointment appointment = new Appointment(
                "A1",
                LocalDate.now(),
                LocalTime.now(),
                "Scheduled",
                patient,
                doctor
        );

        appointment.cancel();

        Report report = new Report("R1", "Billing");
        report.generate();

        System.out.println("System running successfully.");
        // Logger
        Logger logger1 = Logger.getInstance();
        Logger logger2 = Logger.getInstance();

        System.out.println("Same logger instance? " + (logger1 == logger2));
    }
}
```



#### Error stacktrace:

```
scala.collection.Iterator$$anon$19.next(Iterator.scala:973)
	scala.collection.Iterator$$anon$19.next(Iterator.scala:971)
	scala.collection.mutable.MutationTracker$CheckedIterator.next(MutationTracker.scala:76)
	scala.collection.IterableOps.head(Iterable.scala:222)
	scala.collection.IterableOps.head$(Iterable.scala:222)
	scala.collection.AbstractIterable.head(Iterable.scala:935)
	dotty.tools.dotc.interactive.InteractiveDriver.run(InteractiveDriver.scala:164)
	dotty.tools.pc.CachingDriver.run(CachingDriver.scala:45)
	dotty.tools.pc.WithCompilationUnit.<init>(WithCompilationUnit.scala:31)
	dotty.tools.pc.SimpleCollector.<init>(PcCollector.scala:351)
	dotty.tools.pc.PcSemanticTokensProvider$Collector$.<init>(PcSemanticTokensProvider.scala:63)
	dotty.tools.pc.PcSemanticTokensProvider.Collector$lzyINIT1(PcSemanticTokensProvider.scala:63)
	dotty.tools.pc.PcSemanticTokensProvider.Collector(PcSemanticTokensProvider.scala:63)
	dotty.tools.pc.PcSemanticTokensProvider.provide(PcSemanticTokensProvider.scala:88)
	dotty.tools.pc.ScalaPresentationCompiler.semanticTokens$$anonfun$1(ScalaPresentationCompiler.scala:111)
```
#### Short summary: 

java.util.NoSuchElementException: next on empty iterator