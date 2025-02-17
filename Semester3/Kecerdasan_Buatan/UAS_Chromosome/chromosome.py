import numpy as np
import matplotlib.pyplot as plt

# Genetic Algorithm Parameters
num_chromosomes = 10  # Number of chromosomes
num_generations = 10  # Number of generations
num_genes = 5         # Number of genes per chromosome
mutation_rate = 0.1   # Mutation rate
crossover_rate = 0.7  # Crossover rate

# Objective Function
# f(x) = abs((a + 2b + 3c + 4d + 5e) - 50)
def objective_function(chromosome):
    weights = np.array([1, 2, 3, 4, 5])
    return abs(np.dot(weights, chromosome) - 50)

# Fitness Function
def fitness_function(chromosome):
    return 1 / (1 + objective_function(chromosome))

# Generate Initial Population
def generate_population():
    population = np.random.randint(0, 31, (num_chromosomes, num_genes))
    print("Step 1: Initial Population")
    for i, chromosome in enumerate(population):
        print(f"Chromosome[{i + 1}] = {chromosome}")
    return population

# Selection (Roulette Wheel Selection)
def select_population(population):
    fitness_values = np.array([fitness_function(ch) for ch in population])
    probabilities = fitness_values / fitness_values.sum()
    cumulative_probabilities = np.cumsum(probabilities)
    selected_population = []

    print("\nStep 5: Selection")
    for _ in range(num_chromosomes):
        rand = np.random.rand()
        for i, cum_prob in enumerate(cumulative_probabilities):
            if rand <= cum_prob:
                selected_population.append(population[i])
                print(f"Selected Chromosome: {population[i]} with Fitness: {fitness_values[i]:.4f}")
                break

    # Display Roulette Wheel Probabilities
    plt.figure(figsize=(8, 6))
    plt.pie(probabilities, labels=[f"Chromosome {i+1}" for i in range(len(population))], autopct="%1.1f%%")
    plt.title("Roulette Wheel Selection Probabilities")
    plt.show()

    return np.array(selected_population)

# Crossover (Single-Point)
def crossover(parents):
    offspring = []
    print("\nStep 6: Crossover")
    for i in range(0, len(parents), 2):
        if i + 1 < len(parents) and np.random.rand() < crossover_rate:
            crossover_point = np.random.randint(1, num_genes)
            parent1, parent2 = parents[i], parents[i + 1]
            child1 = np.concatenate((parent1[:crossover_point], parent2[crossover_point:]))
            child2 = np.concatenate((parent2[:crossover_point], parent1[crossover_point:]))
            offspring.extend([child1, child2])
            print(f"Parents: {parent1}, {parent2} | Crossover Point: {crossover_point} | Children: {child1}, {child2}")
        else:
            offspring.extend(parents[i:i+2])
            print(f"No Crossover for Parents: {parents[i:i+2]}")
    return np.array(offspring)

# Mutation
def mutate(population):
    print("\nStep 7: Mutation")
    for i, chromosome in enumerate(population):
        if np.random.rand() < mutation_rate:
            gene_to_mutate = np.random.randint(0, num_genes)
            old_value = chromosome[gene_to_mutate]
            chromosome[gene_to_mutate] = np.random.randint(0, 31)
            print(f"Chromosome[{i + 1}] Gene[{gene_to_mutate}] Mutated: {old_value} -> {chromosome[gene_to_mutate]}")
    return population

# Genetic Algorithm Execution
def genetic_algorithm():
    population = generate_population()

    for generation in range(num_generations):
        print(f"\nGeneration {generation + 1}")

        # Step 3: Display Current Generation Population
        print("Step 3: Current Population")
        fitness_values = [fitness_function(ch) for ch in population]
        for i, chromosome in enumerate(population):
            print(f"Chromosome[{i + 1}] = {chromosome} | Fitness = {fitness_values[i]:.4f}")

        # Evaluate and display best chromosome
        best_chromosome = population[np.argmax(fitness_values)]
        print(f"\nStep 4: Evaluation - Best Chromosome: {best_chromosome}, Fitness: {max(fitness_values):.4f}")

        # Selection
        selected_population = select_population(population)

        # Crossover
        offspring = crossover(selected_population)

        # Mutation
        population = mutate(offspring)

    # Final Solution
    best_chromosome = population[np.argmax([fitness_function(ch) for ch in population])]
    final_fitness = fitness_function(best_chromosome)
    print("\nFinal Best Chromosome:", best_chromosome)
    print("Final Fitness Value:", final_fitness)
    print("Final Objective Value:", objective_function(best_chromosome))

    

# Run the Genetic Algorithm
genetic_algorithm()
