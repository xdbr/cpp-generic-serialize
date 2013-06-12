require 'rake/clean'

CXX      = 'g++'
CXXFLAGS = '-std=c++11 -Wall -Wextra'
SOURCES  = FileList['test*.cpp']
OBJECTS  = SOURCES.map { |file| file.ext('.o') }
EXE      = SOURCES.map { |file| file.ext('.test') }

CLEAN.include(OBJECTS, EXE)

task :default => :test

desc "Run all tests (default)"
multitask :test => EXE do
  sh "./#{EXE}"
end

rule '.o' => ['.cpp'] do |t|
  sh "#{CXX} #{CXXFLAGS} #{t.source} -c -o #{t.name}"
end

rule '.test' => ['.cpp'] do |t|
  sh "#{CXX} #{CXXFLAGS} #{t.source} -o #{t.name}"
end

