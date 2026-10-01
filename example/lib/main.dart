import 'package:material_ui/material_ui.dart';


void main() {
  runApp(const MaterialApp(
    restorationScopeId: 'root',
    home: CounterScreen(),
  ));
}

class const CounterScreen({ super.key, }) extends StatefulWidget {
  @override
  State<CounterScreen> createState() => _CounterScreenState();
}

class _CounterScreenState extends State<CounterScreen> with RestorationMixin {
  late RestorableInt _counter;

  @override
  String? get restorationId => 'cs';

  @override
  void initState() {
    super.initState();
    _counter = .new(0);
  }

  @override
  void restoreState(RestorationBucket? oldBucket, bool initialRestore) {
    registerForRestoration(_counter, 'c');
  }

  @override
  void dispose() {
    super.dispose();
    _counter.dispose();
  }

  @override
  Widget build(BuildContext context) => Scaffold(
    restorationId: 's',
    drawer: const Drawer(
      child: Text('Drawer'),
    ),
    appBar: AppBar(
      title: const Text('Restoration example'),
    ),
    body: Center(
      child: Text('Counter: ${_counter.value}'),
    ),
    floatingActionButton: FloatingActionButton(
      onPressed: () => setState(() {
        _counter.value++;
      }),
    ),
  );
}
