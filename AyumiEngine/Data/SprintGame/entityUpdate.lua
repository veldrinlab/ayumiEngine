-- Entity update script - TEST
-- Szymon "Veldrin" Jab³oñski
-- 05.10.2011

delta = Scene:getDeltaTime()

position = Entity:getEntityPosition()

newPosition = {position[1],position[2],position[3]}

newPosition[2] = newPosition[2] + 1.0 * delta
Entity:setEntityPosition(newPosition[1],newPosition[2],newPosition[3])

--position[1] +=  5.0
--Entity:setEntityPosition(0,10,0)


