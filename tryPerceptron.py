import torch
import torch.nn as nn

class Perceptron(nn.Module):
    def __init__(self):
        super(Perceptron, self).__init__()
        self.linear = nn.Linear(2, 4)
        self.hidden = nn.Linear(4, 1)

    def forward(self, input):
        input = torch.sigmoid(self.linear(input))
        output = torch.sigmoid(self.hidden(input))
        return output


x = torch.tensor([[0.0, 0.0],
                  [0.0, 1.0],
                  [1.0, 0.0],
                  [1.0, 1.0]], dtype=torch.float32)

y = torch.tensor([[0.0],
                  [1.0],
                  [1.0],
                  [0.0]], dtype=torch.float32)

model = Perceptron()

criterion = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.01)

# Train the model
for epoch in range(10000): 
    # Forward pass
    y_pred = model(x)

    loss = criterion(y_pred, y)

    # Backward pass
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

  
# Test the model
with torch.no_grad():  
    y_pred = model(x)
    predicted = (y_pred > 0.5).float() 
    print(f'Predicted outputs:\n{predicted}')
    # print(f'Actual outputs:\n{y}')

