


struct PrimeSifter {
    let n: Int
    var a: [Bool]
    var f: Bool
    
    var result: [Int]? {
        if f == false {
            return nil
        }
        
        var result = [Int]()
        
        for i in 2..<n {
            if a[i] == false {
                result.append(i)
            }
        }
        
        return result
    }
    
    init(n:Int) {
        self.n = n
        self.a = [Bool](repeating:false, count:n)
        self.f = false
    }
    
    mutating func sift() {
        let ub = Int(Float(n).squareRoot()) + 1
        for i in 2...ub {
            print("==>", i, a.count)
            if a[i] == true {
                continue
            }
            
            var c = i * i
            while c < n {
                a[c] = true
                c += i
            }
        }
        
        self.f = true
    }
}


#if false
 var ps = PrimeSifter(n:6)
 ps.sift()
 print(ps.result!)
#endif

