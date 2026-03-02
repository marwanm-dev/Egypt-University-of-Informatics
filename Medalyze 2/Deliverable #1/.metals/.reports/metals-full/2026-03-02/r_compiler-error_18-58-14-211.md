file://<HOME>/projects/Egypt-University-of-Informatics/Medalyze%202/Deliverable%20%231/medalyze/src/main/java/com/medalyze/Report.java
### java.util.NoSuchElementException: next on empty iterator

occurred in the presentation compiler.

presentation compiler configuration:


action parameters:
uri: file://<HOME>/projects/Egypt-University-of-Informatics/Medalyze%202/Deliverable%20%231/medalyze/src/main/java/com/medalyze/Report.java
text:
```scala
package com.medalyze;

public class Report {

    private String reportID;
    private String reportType;

    public Report(String reportID, String reportType) {
        this.reportID = reportID;
        this.reportType = reportType;
    }

    public String getReportID() {
        return reportID;
    }

    public String getReportType() {
        return reportType;
    }

public void generate() {
    System.out.println("Generating " + reportType + " report...");
    Logger.getInstance().log(reportType + " report generated.");
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