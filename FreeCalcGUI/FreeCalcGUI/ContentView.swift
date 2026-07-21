import SwiftUI

struct ContentView: View {
    @State private var aText: String = ""
    @State private var bText: String = ""
    @State private var opIndex: Int = 0
    @State private var resultText: String = ""
    
    var body: some View {
        VStack(spacing: 16) {
            HStack(spacing: 12) {
                TextField("数字a", text: $aText)
                    .frame(width: 140)
                TextField("数字b", text: $bText)
                    .frame(width: 140)
            }
            Picker("", selection: $opIndex) {
                Text("1加").tag(0)
                Text("2减").tag(1)
                Text("3乘").tag(2)
                Text("4除").tag(3)
            }
            .pickerStyle(.segmented)
            Button("开始计算") {
                calc()
            }
            Text(resultText)
                .font(.title)
        }
        .padding(20)               
        .frame(width: 360, height: 260)
    }
    
    func calc() {
        guard let a = Double(aText), let b = Double(bText) else {
            resultText = ""
            return
        }
        let c = opIndex + 1
        var out: Double = 0
        if c == 1 {
            out = a + b
        } else if c == 2 {
            out = a - b
        } else if c == 3 {
            out = a * b
        } else if c == 4 {
            if b == 0 {
                resultText = "0不能是除数"
                return
            }
            out = a / b
        }
        if out.truncatingRemainder(dividingBy: 1) == 0 {
            resultText = "\(Int(out))"
        } else {
            resultText = String(format: "%.2f", out)
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
