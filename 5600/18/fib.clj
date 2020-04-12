(defn fib [x]
  (if (< x 2)
    1
    (+ (fib (- x 1))
       (fib (- x 2)))))

(def nums (into [] (repeat 5 40)))

(time (println (pmap fib nums)))

(shutdown-agents)
