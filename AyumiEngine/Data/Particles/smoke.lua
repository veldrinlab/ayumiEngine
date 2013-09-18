-- Post process effetcs load script
-- Szymon "Veldrin" Jab³oñski
-- 11.11.2011

name = "Smoke"
Particles:setVelocity({0.0, 0.0, 0.0});
Particles:setRotation({1.0, 1.0, 1.0});
Particles:setAcceleration({1.0, 1.0, 1.0});
Particles:setColor({1.0, 0.5, 0.0,0.0})
Particles:setSize(3.0);
Particles:setLifeTime(1.0);
Particles:setParticleAmount(20);
Particles:setEmiterShader("SmokeParticles");
Particles:setEmiterTexture("Particle");
