ECppS

***Work in progress***

TODO README

Components, Systems and Entities definitions are made using Builder pattern.

### Components
Components are somewhat "strongly" defined. You can't append new variables to component during runtime.
```lua
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
Entities are just a bunch of components and init(done) function
```lua
-- Box.lua
local A = dofile('A.lua')
return ECS.makeEntityDef('Box')
                    :component(A, 'Box') -- Component -> Args to Component init function
                    :done(function(self, x, y)
                        self[A].x = x
                        self[A].y = y
                    end)
```

### Systems
```lua
-- TestSystem.lua
local DepSystem = dofile('DepSystem.lua')
return ECS.makeEntityDef('Test')
                    :init(function(self) -- 
                        
                    end)
                    :process(function(self, entities) -- System logic
                    
                    end)
                    :depends(DepSystem) -- This system needs these systems to be done to be processed
```

