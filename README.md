ECppS

***Work in progress***

TODO README

Components, Systems and Entities definitions are made using Builder pattern.

### Components
Components are somewhat "strongly" defined. You can't append new variables to component during runtime.
```
-- A.lua
return ECS.makeComponentDef('A')
                    :var('x') -- 'nil' value,
                    :var('y', 0) -- number
                    :var('z', 'test') -- string
                    :var('w', function() print('f()') end)
                    :var_f('foo', function(a, b) return a + b end, 10, 20)
                    :done(function(self, c) -- or just done() if you don't need init function
                        self.z = c
                    end) 
```
### Entities
```
-- Box.lua
local A = dofile('A.lua')
return ECS.makeEntityDef('Box')
                    :component(A, 'Box') -- Args-> Component -> Args to Component init function
                    :done(function(self, x, y)
                        self[A].x = x
                        self[A].y = y
                    end
```
